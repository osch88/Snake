#include "food.h"

#include <time.h>

#include <cstdlib>

#include "engine.h"
#include "utilities.h"

void Food::Init()
{
    std::cout << "Food initialized\n";
    NewPos();
}

void Food::NewPos()
{
    Vec2 rdmPos;
    std::srand(time(0));
    rdmPos.x = rand() % (Utilities::Instance().GetNumersOfTiles() - 1);
    rdmPos.y = rand() % (Utilities::Instance().GetNumersOfTiles() - 1);

    rect_.x = rdmPos.x * Utilities::Instance().GetTileWidth();
    rect_.y = rdmPos.y * Utilities::Instance().GetTileHeight();
    rect_.h = Utilities::Instance().GetTileHeight();
    rect_.w = Utilities::Instance().GetTileWidth();

    SetPos(rdmPos);
}

void Food::Update() {}

void Food::Draw(SDL_Renderer* renderer)
{
    // Draw rectangle
    SDL_SetRenderDrawColor(renderer, 255, 100, 100,
                           255);
    SDL_RenderFillRect(renderer, &rect_);
    // Draw outerline of rectangle
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect_);
}
