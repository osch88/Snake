#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "iobject.h"
#include "utilities.h"
#include "vector2d.h"

class Food: public IObject {
public:
    Food(const int x, const int y) : IObject(x, y) { Init(); }
    void Init();
    void Update() override;
    void Draw() override;
    void NewPos();

private:
    SDL_Rect rect_;
};
