#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "vector2d.h"

class IObject {
public:
    IObject(const int col, const int row)
    {
        pos_.x = col;
        pos_.y = row;
        std::cout << "IObject initilized with col: " << col << " row: " << row
                  << std::endl;
    }
    virtual void Update() = 0;
    virtual void Draw() = 0;
    // virtual void Move(int x, int y) = 0;

    Vec2 GetPos() { return pos_; }
    void SetPos(Vec2 vec) { pos_ = vec; }
    void SetPos();

private:
    Vec2 pos_;
};
