

#include <string>
#include <SDL2/SDL.h>
#include <GameEngine/Game.h>
#include <GameEngine/Texture.h>
#include <GameEngine/Clock.h>
#include <GameEngine/ColorList.h>

constexpr int windowWidth{};
constexpr int windowHeight{};


int main(int argv, char** argc)
{
    GameEngine::Game geGame{ "The Game!", windowWidth, windowHeight };

    geGame.init();

    //GameEngine::Texture tiles, background, frame;
    
    bool isRunning{ true };    

    SDL_Event event;
    while (isRunning)
    {
        
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:   // exit game
                    isRunning = false;
                    break;

                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                default:
                    break;
                }
                break;
            }
        }


        ///////Tick//////

       

        geGame.clear(GameEngine::ColorList::black);
        /////////draw//////////
       
        geGame.updateScreen();
    }

    return 0;
}
