#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include <string>

#include "vector2d.h"

class IObject {
public:
    IObject(const Vec2 vec) : pos_(vec)
    {
        std::cout << "IObject initilized with col: " << pos_.x
                  << " row: " << pos_.y << std::endl;
    }
    IObject() { pos_ = {0, 0}; }
    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
    // virtual void Move(int x, int y) = 0;

    Vec2 GetPos() { return pos_; }
    void SetPos(Vec2 vec) { pos_ = vec; }
    void SetPos();

private:
    Vec2 pos_;
};
