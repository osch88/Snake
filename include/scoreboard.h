#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "iobject.h"

class Scoreboard : public IObject {
public:
    Scoreboard()
        : IObject(),
          rect_{400, 10, 0, 0},
          score_{0},
          color_{0, 0, 0, 0},
          fontSize_{70}
    {
        Init();
    }
    void Init();
    void Update() override;
    void Draw(SDL_Renderer* renderer) override;
    void SetScore(const int x);

private:
    SDL_Rect rect_;
    int score_;
    SDL_Color color_;
    TTF_Font* font_;
    SDL_Texture* texture_;
    int fontSize_;
    std::string msg_;
};
