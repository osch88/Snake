#pragma once
#include "SDL2/SDL.h"

class Input {
public:
    static Input& GetInstance()
    {
        static Input* instance_ = new Input();
        return *instance_;
    }
    void Listen();
    bool GetKeyDown(SDL_Scancode key);

private:
    Input();

    void KeyUp();
    void KeyDown();

    const Uint8* m_KeyStates;

    static Input* instance_;
};
