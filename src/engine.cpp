#include "engine.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>

#include <iterator>
#include <memory>

#include "food.h"
#include "input.h"
#include "iobject.h"
#include "scoreboard.h"
#include "snake.h"
#include "utilities.h"

bool Engine::Init()
{
    // Init SDL Image
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if (SDL_Init(SDL_INIT_VIDEO) != 0 || (initted & flags) != flags) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Init SDL Font
    if (TTF_Init() == -1) {
        SDL_Log("Failed eto initialize SDL: %s", SDL_GetError());
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
    Vec2 snakeVec = {5, 5};
    std::shared_ptr<IObject> snake = std::make_unique<Snake>(snakeVec);
    std::shared_ptr<IObject> food = std::make_unique<Food>();
    std::shared_ptr<IObject> score = std::make_unique<Scoreboard>();
    objects_["food"] = food;
    objects_["snake"] = snake;
    objects_["score"] = score;

    scoreboard_ = 0;

    return isRunning_ = true;
}

void Engine::Update()
{
    for (auto const& [name, ptr] : objects_) {
        ptr->Update();
    }
    // Get Food location
    Vec2 foodLoc = objects_["food"]->GetPos();

    // Check if food is within snake parameters
    bool foodWithin =
        std::static_pointer_cast<Snake>(objects_["snake"])
            ->Collision(foodLoc, [](int x) { return x > 0 ? true : false; });

    // If equal,
    if (foodWithin) {
        std::static_pointer_cast<Food>(objects_["food"])->NewPos();
        std::static_pointer_cast<Snake>(objects_["snake"])->Grow();
    }
    const int snakeLength =
        std::static_pointer_cast<Snake>(objects_["snake"])->GetSnakeSize();
    std::static_pointer_cast<Scoreboard>(objects_["score"])
        ->SetScore(snakeLength);
}

void Engine::Render()
{
    // Render background - canvas
    SDL_SetRenderDrawColor(renderer_, 155, 204, 153, 255);
    SDL_RenderClear(renderer_);

    // Render objects
    for (auto const& [name, ptr] : objects_) {
        ptr->Draw(renderer_);
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
