#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>

#include <functional>
#include <vector>

#include "iobject.h"
#include "utilities.h"
#include "vector2d.h"

enum Direction { UP, RIGHT, DOWN, LEFT, NONE };

class Body {
public:
    Body(Vec2 pos, bool head) : pos_(pos), head_{head} {}
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
    bool IsHead() { return head_; }

private:
    Vec2 pos_;
    SDL_Rect rect_;
    bool head_;
};

class Snake : public IObject {
public:
    Snake(const int x, const int y) : IObject(x, y) { Init(); }
    void Init();
    void Update() override;
    void Draw(SDL_Renderer* renderer) override;
    void Grow();
    bool GetCollision() { return dead_; }
    bool Collision(Vec2 object, std::function<bool(int)> func);

private:
    void Move();
    void GetDirection();
    std::vector<Body> bodies_;
    SDL_Rect rect_;
    Vec2 pos_;
    Direction dir_;
    int size_;
    Vec2 tail_;
    bool dead_;
    SDL_Color colorHead_;
    SDL_Color colorBody_;
    SDL_Color colorDead_;
};
