#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "iobject.h"
#include "vector2d.h"

struct Body {
    Vec2 pos;
    SDL_Rect rect;
    SDL_Color color;
};

class Snake : public IObject {
public:
    Snake(const int x, const int y) : IObject(x, y) {
        Init();
    }
    void Init();
    void Update() override;
    void Draw() override;
    void Move(int x, int y) override;

private:
    std::vector<Body> bodies;
};
