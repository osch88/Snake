#include "snake.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <iostream>
#include <vector>

#include "engine.h"
#include "input.h"
#include "utilities.h"

void Snake::Init()
{
    std::cout << "Snake initialized\n";

    // Set the colors
    colorHead_ = {155, 221, 76, 255};
    colorBody_ = {255, 221, 76, 255};
    colorDeadBody_ = {150, 150, 150, 255};
    colorDeadHead_ = {75, 75, 75, 255};

    // Initial body size
    size_ = 5;
    int initlizedX = GetPos().x;
    int initlizedY = GetPos().y;

    for (int i = 0; i < size_; i++) {
        // Set position
        Vec2 vec;
        vec.x = initlizedX + i;
        vec.y = initlizedY;
        // Make head unique
        bool isHead = i == 0 ? true : false;
        Body b(vec, isHead);

        b.UpdateRect();
        bodies_.push_back(b);
    }
    dir_ = NONE;
    dead_ = false;
}

void Snake::GetDirection()
{
    if (Input::Instance().GetKeyDown(SDL_SCANCODE_A)) {
        if (dir_ != RIGHT) dir_ = LEFT;
    }
    else if (Input::Instance().GetKeyDown(SDL_SCANCODE_D)) {
        if (dir_ != LEFT) dir_ = RIGHT;
    }
    else if (Input::Instance().GetKeyDown(SDL_SCANCODE_W)) {
        if (dir_ != DOWN) dir_ = UP;
    }
    else if (Input::Instance().GetKeyDown(SDL_SCANCODE_S)) {
        if (dir_ != UP) dir_ = DOWN;
    }
}

void Snake::Update()
{
    if (!dead_) {
        GetDirection();
        /*
         * This is used in case the snake grow
         */
        tail_ = bodies_[size_].GetPos();
        Move();
    }
}

void Snake::Draw(SDL_Renderer *renderer)
{
    for (auto &b : bodies_) {
        // Draw rectangle
        SDL_Rect r = b.GetRect();

        if (!dead_) {
            if (b.IsHead()) {
                SDL_SetRenderDrawColor(renderer, colorHead_.r, colorHead_.g,
                                       colorHead_.b, colorHead_.a);
            }
            else {
                SDL_SetRenderDrawColor(renderer, colorBody_.r, colorBody_.g,
                                       colorBody_.b, colorBody_.a);
            }
        }
        else {
            if (b.IsHead()) {
                SDL_SetRenderDrawColor(renderer, colorDeadHead_.r, colorDeadHead_.g,
                                       colorDeadHead_.b, colorDeadHead_.a);
            }
            else {
                SDL_SetRenderDrawColor(renderer, colorDeadBody_.r, colorDeadBody_.g,
                                       colorDeadBody_.b, colorDeadBody_.a);
            }
        }
        SDL_RenderFillRect(renderer, &r);
        // Draw outerline of rectangle
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &r);
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

    /*
     * NONE -> Snake waiting for user input
     * !NONE -> The snake is on the move
     */
    if (dir_ != NONE) {
        Vec2 vec = bodies_[0].GetPos();
        Vec2 previous = vec;
        vec.x += x;
        vec.y += y;
        auto tiles = Utilities::Instance().GetNumersOfTiles();

        if (vec.x > tiles - 1) {
            vec.x = 0;
        }
        if (vec.x < 0) {
            vec.x = tiles;
        }
        if (vec.y > tiles - 1) {
            vec.y = 0;
        }
        if (vec.y < 0) {
            vec.y = tiles;
        }

        dead_ = Collision(vec, [](int x) { return x > 0 ? true : false; });
        if(dead_) return;
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
    Body b(tail_, false);
    b.UpdateRect();

    bodies_.push_back(b);

    size_ = bodies_.size();
}

bool Snake::Collision(Vec2 object, std::function<bool(int)> func)
{
    int i{0};
    for (auto &b : bodies_) {
        if (b.GetPos() == object) {
            i++;
        }
    }
    auto respons = func(i);
    return respons;
}
