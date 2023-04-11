#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "iobject.h"
#include "utilities.h"
#include "vector2d.h"

enum Direction { UP, RIGHT, DOWN, LEFT, NONE };

class Body {
public:
    Body(Vec2 pos) : pos_(pos) {}
    void UpdateRect()
    {
        rect_.x = pos_.x * Utilities::Instance().GetTileWidth();
        rect_.y = pos_.y * Utilities::Instance().GetTileHeight();
        rect_.h = Utilities::Instance().GetTileHeight();
        rect_.w = Utilities::Instance().GetTileWidth();
    }
    void UpdatePos(Vec2 vec) { pos_ = vec; }
    Vec2 GetPos() { return pos_; }
    SDL_Rect GetRect() { return rect_; }

private:
    Vec2 pos_;
    SDL_Rect rect_;
    SDL_Color color;
};

class Snake : public IObject {
public:
    Snake(const int x, const int y) : IObject(x, y) { Init(); }
    void Init();
    void Update() override;
    void Draw() override;
    void Move();
    void Grow();

private:
    std::vector<Body> bodies_;
    SDL_Rect rect_;
    Vec2 pos_;
    Direction dir_;
    int size_;
    Vec2 tail_;
};
