#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "iobject.h"

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
    std::map<std::string, std::shared_ptr<IObject>> objects_;
    std::list<std::string> rendering_order_;

    int scoreboard_;
};
