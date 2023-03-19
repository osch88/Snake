#include "engine.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>

#include "input.h"
#include "snake.h"
#include "utilities.h"

Snake *snake = nullptr;

bool Engine::Init()
{
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

    // Load level

    // Load Objects
    snake = new Snake(5,5);

    return isRunning_ = true;
}

void Engine::Update() {}

void Engine::Render()
{
    // Present render
    SDL_RenderPresent(renderer_);
}

void Engine::Events() { Input::GetInstance().Listen(); }

bool Engine::Clean()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit() { isRunning_ = false; }
