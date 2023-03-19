#include "snake.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include <iostream>

#include "engine.h"
#include "utilities.h"

void Snake::Init()
{
    std::cout << "Snake initialized\n";
    rect_.x = GetPos().x * Utilities::Instance().GetTileWidth();
    rect_.y = GetPos().y * Utilities::Instance().GetTileHeight();
    rect_.h = Utilities::Instance().GetTileHeight();
    rect_.w = Utilities::Instance().GetTileWidth();
}

void Snake::Update() {}

void Snake::Draw()
{
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 
                           255, 221, 76, 255);
    SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect_);
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 
                           0, 0, 0, 255);
    SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rect_);

}

void Snake::Move(int x, int y) {}
