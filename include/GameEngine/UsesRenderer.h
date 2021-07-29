#pragma once

#include <string>
#include <SDL2/SDL.h>


namespace GameEngine
{
    class Game;
    class UsesRenderer
    {
        static SDL_Renderer* renderer;
    public:

        static SDL_Renderer* getRenderer();

        friend class Game;
    };
}
