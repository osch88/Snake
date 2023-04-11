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
    int noTiles = Utilities::Instance().GetNumersOfTiles();

    Vec2 rdmPos;
    std::srand(time(0));
    rdmPos.x = rand() % (Utilities::Instance().GetNumersOfTiles() - 1);
    rdmPos.y = rand() % (Utilities::Instance().GetNumersOfTiles() - 1);

    rect_.x = rdmPos.x * Utilities::Instance().GetTileWidth();
    rect_.y = rdmPos.y * Utilities::Instance().GetTileHeight();
    rect_.h = Utilities::Instance().GetTileHeight();
    rect_.w = Utilities::Instance().GetTileWidth();

    SetPos(rdmPos);

    // std::cout << "Food: " << rect_.x << " " << rect_.y << std::endl;
}

void Food::Update() {}

void Food::Draw()
{
    // Draw rectangle
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 100, 100,
                           255);
    SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect_);
    // Draw outerline of rectangle
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rect_);
}
