#include "scoreboard.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "utilities.h"

void Scoreboard::Init()
{
    // Load font
    const char* path = "../assets/font/8bitOperatorPlus8-Regular.ttf";
    font_ = TTF_OpenFont(path, fontSize_);

    if (font_ == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }

    std::cout << "Scoreboard initialized\n";
}

void Scoreboard::Update() { msg_ = std::to_string(score_); }

void Scoreboard::Draw(SDL_Renderer* renderer)
{
    // Render
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(font_, msg_.c_str(), color_);
    if (text_surface == nullptr) {
        SDL_Log("Failed to load text_surface: %s", TTF_GetError());
        return;
    }
    texture_ = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (texture_ == nullptr) {
        SDL_Log("Failed to create font texture: %s", SDL_GetError());
        return;
    }
    rect_.w = text_surface->w;
    rect_.h = text_surface->h;
    rect_.x = Utilities::Instance().GetScreenWidth() / 2 - rect_.w / 2;
    SDL_FreeSurface(text_surface);
    SDL_RenderCopy(renderer, texture_, NULL, &rect_);
}

void Scoreboard::SetScore(const int x) { score_ = x; }
