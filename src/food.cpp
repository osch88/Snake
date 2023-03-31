#include "food.h"

#include "engine.h"
#include "utilities.h"

void Food::Init()
{
    std::cout << "Food initialized\n";
    this->SetPosition();
}

void Food::SetPosition()
{
    // TODO: set a random number within canvas
    int noTiles = Utilities::Instance().GetNumersOfTiles();

    pos_.x = this->GetPos().x;
    pos_.y = this->GetPos().y;

    rect_.x = pos_.x * Utilities::Instance().GetTileWidth();
    rect_.y = pos_.y * Utilities::Instance().GetTileHeight();
    rect_.h = Utilities::Instance().GetTileHeight();
    rect_.w = Utilities::Instance().GetTileWidth();

    std::cout << "Food: " << rect_.x << " " << rect_.y << std::endl;
}

void Food::Update() {}

void Food::Draw()
{
    // Draw rectangle
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 100, 100, 255);
    SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect_);
    // Draw outerline of rectangle
    SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawRect(Engine::Instance().GetRenderer(), &rect_);
}
