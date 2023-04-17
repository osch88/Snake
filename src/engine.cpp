#include "engine.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include <iterator>
#include <memory>

#include "food.h"
#include "input.h"
#include "iobject.h"
#include "snake.h"
#include "utilities.h"

bool Engine::Init()
{
    Utilities::Instance().SetScreenWidth(900);
    Utilities::Instance().SetScreenHeight(900);

    // Init SDL
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if (SDL_Init(SDL_INIT_VIDEO) != 0 || (initted & flags) != flags) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Create Window
    window_ = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               Utilities::Instance().GetScreenWidth(),
                               Utilities::Instance().GetScreenHeight(), 0);

    if (window_ == nullptr) {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    // Create Renderer
    renderer_ = SDL_CreateRenderer(
        window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer_ == nullptr) {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    // Load Objects
    std::shared_ptr<IObject> snake = std::make_unique<Snake>(5,5);
    std::shared_ptr<IObject> food = std::make_unique<Food>(5,10);
    objects_["food"] = food;
    objects_["snake"] = snake;

    return isRunning_ = true;
}

void Engine::Update()
{
    for (auto const& [name, ptr] : objects_) {
        ptr->Update();
    }

    // Get Food location
    auto foodLoc = objects_["food"]->GetPos();
    // Get Snake location
    auto snakeLoc = objects_["snake"]->GetPos();
    // If equal,
    if (foodLoc == snakeLoc) {
        std::static_pointer_cast<Food>(objects_["food"])->NewPos();
        std::static_pointer_cast<Snake>(objects_["snake"])->Grow();
    }
}

void Engine::Render()
{
    // Render background - canvas
    SDL_SetRenderDrawColor(renderer_, 155, 204, 153, 255);
    SDL_RenderClear(renderer_);

    // Render background - lines
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    for (int i = Utilities::Instance().GetTileWidth();
         i < Utilities::Instance().GetScreenWidth();
         i += Utilities::Instance().GetTileWidth()) {
        SDL_RenderDrawLine(renderer_, i, 0, i,
                           Utilities::Instance().GetScreenHeight());
    }
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    for (int i = Utilities::Instance().GetTileHeight();
         i < Utilities::Instance().GetScreenHeight();
         i += Utilities::Instance().GetTileHeight()) {
        SDL_RenderDrawLine(renderer_, 0, i,
                           Utilities::Instance().GetScreenWidth(), i);
    }
    // Render objects
    for (auto const& [name, ptr] : objects_) {
        ptr->Draw();
    }

    // Present render
    SDL_RenderPresent(renderer_);
}

void Engine::Events() { Input::Instance().Listen(); }

bool Engine::Clean()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit() { isRunning_ = false; }
