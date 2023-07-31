#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "engine.h"
#include "utilities.h"

constexpr int WIDTH = 900;
constexpr int HEIGHT = 900;

int main(/* int argc, char **argv */)
{
    Utilities::Instance().SetScreenWidth(WIDTH);
    Utilities::Instance().SetScreenHeight(HEIGHT);

    Engine::Instance().Init();
    Engine::Instance().Run();

    return 0;
}
