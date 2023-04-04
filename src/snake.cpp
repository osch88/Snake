#include "snake.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <iostream>

#include "engine.h"
#include "input.h"
#include "utilities.h"

void Snake::Init()
{
    std::cout << "Snake initialized\n";

    size_ = 5;
    int initlizedX = GetPos().x;
    int initlizedY = GetPos().y;

    for (int i = 0; i < size_; i++) {
        Vec2 vec;
        vec.x = initlizedX + i;
        vec.y = initlizedY;
        Body b(vec);
        b.UpdateRect();

        bodies_.push_back(b);
    }
    dir_ = NONE;
}

void Snake::Update()
{
    if (Input::Instance().GetKeyDown(SDL_SCANCODE_A)) {
        if (dir_ != RIGHT) dir_ = LEFT;
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_D)) {
        if (dir_ != LEFT) dir_ = RIGHT;
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_W)) {
        if (dir_ != DOWN) dir_ = UP;
    }

    if (Input::Instance().GetKeyDown(SDL_SCANCODE_S)) {
        if (dir_ != UP) dir_ = DOWN;
    }

    Move();
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

void Snake::Move()
{
    int x, y;

    switch (dir_) {
        case UP: {
            x = 0;
            y = -1;
            break;
        };
        case RIGHT: {
            x = 1;
            y = 0;
            break;
        }
        case DOWN: {
            x = 0;
            y = 1;
            break;
        }
        case LEFT: {
            x = -1;
            y = 0;
            break;
        }
        default: {
            x = 0;
            y = 0;
        }
    }

    if (dir_ != NONE) {
        Vec2 vec = bodies_[0].GetPos();
        Vec2 previous = vec;
        vec.x += x;
        vec.y += y;

        if (vec.x > Utilities::Instance().GetNumersOfTiles() - 1) {
            vec.x = 0;
        }
        if (vec.x < 0) {
            vec.x = Utilities::Instance().GetNumersOfTiles();
        }
        if (vec.y > Utilities::Instance().GetNumersOfTiles() - 1) {
            vec.y = 0;
        }
        if (vec.y < 0) {
            vec.y = Utilities::Instance().GetNumersOfTiles();
        }

        bodies_[0].UpdatePos(vec);
        this->SetPos(vec);
        bodies_[0].UpdateRect();

        for (int i = 1; i < size_; i++) {
            Vec2 tmp = bodies_[i].GetPos();
            bodies_[i].UpdatePos(previous);
            bodies_[i].UpdateRect();
            previous = tmp;
        }
    }
}

void Snake::Grow()
{
    std::cout << "Snake has been one sizer bigger" << std::endl;
}
