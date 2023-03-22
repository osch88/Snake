#include "snake.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <iostream>

#include "engine.h"
#include "utilities.h"
#include "input.h"

void Snake::Init()
{
    std::cout << "Snake initialized\n";

    int numberOfBodies = 5;
    int initlizedX = GetPos().x;
    int initlizedY = GetPos().y;

    for (int i = 0; i < numberOfBodies; i++) {
        Vec2 vec;
        vec.x = initlizedX+i;
        vec.y = initlizedY;
        Body b(vec);
        b.UpdateRect();

        bodies_.push_back(b);
    }
}

void Snake::Update()
{
    if (Input::Instance().GetKeyDown(SDL_SCANCODE_A)) {
        Move(-1,0);
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_D)) {
        Move(1,0);
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_W)) {
        Move(0,-1);
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_S)) {
        Move(0,1);
    }
}


void Snake::Draw()
{
    for (auto &b : bodies_) {
        // Draw rectangle
        SDL_Rect r = b.GetRect();
        SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 221, 76,
                               255);
        SDL_RenderFillRect(Engine::Instance().GetRenderer(), &r);
        // Draw outerline of rectangle
        SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
        SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &r);
    }
}

void Snake::Move(int x, int y)
{
    Vec2 vec = bodies_[0].GetPos();
    vec.x += x;
    vec.y += y;

    bodies_[0].UpdatePos(vec);
    bodies_[0].UpdateRect();

}
