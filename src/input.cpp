#include "input.h"
#include <SDL2/SDL_scancode.h>

#include "engine.h"

Input::Input() { m_KeyStates = SDL_GetKeyboardState(nullptr); }

void Input::Listen()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
            default:
                break;
        }
    }
    if (GetKeyDown(SDL_SCANCODE_ESCAPE)) Engine::Instance().Quit();
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    return (m_KeyStates[key] == 1);  // 1 is true
}

void Input::KeyUp() { m_KeyStates = SDL_GetKeyboardState(nullptr); }

void Input::KeyDown() { m_KeyStates = SDL_GetKeyboardState(nullptr); }
