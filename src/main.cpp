#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "engine.h"
#include "utilities.h"

int main(int argc, char **argv)
{
    Utilities::Instance().SetScreenWidth(800);
    Utilities::Instance().SetScreenHeight(800);
    Engine::Instance().Init();

    Uint64 firstFrame, lastFrame, elapsed;

    while (Engine::Instance().IsRunning()) {
        firstFrame = SDL_GetPerformanceCounter();

        Engine::Instance().Events();
        Engine::Instance().Update();
        Engine::Instance().Render();

        lastFrame = SDL_GetPerformanceCounter();
        elapsed = firstFrame - lastFrame;

        float elapsed =
            (lastFrame - firstFrame) / (float)SDL_GetPerformanceFrequency();
        // std::cout << "Current FPS: " << std::to_string(1.0f / elapsed)
        //           << std::endl;
        SDL_Delay(100 - elapsed);
    }

    Engine::Instance().Clean();
    return 0;
}
