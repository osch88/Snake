#include "snake.h"

#include <iostream>
#include <SDL2/SDL.h>
#include "engine.h"

void Snake::Init()
{
    std::cout << "Snake initialized\n";
}

void Snake::Update() {}

void Snake::Draw()
{
    SDL_Rect rect {0,0, 80, 80};
    SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
}

void Snake::Move(int x, int y) {}
