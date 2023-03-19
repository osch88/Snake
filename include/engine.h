#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

class Engine {
public:
    static Engine& Instance()
    {
        static Engine* instance_ = new Engine();
        return *instance_;
    }

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    bool IsRunning() { return isRunning_; }
    SDL_Renderer* GetRenderer() { return renderer_; }

private:
    Engine() {}
    bool isRunning_;
    static Engine* instance_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
};