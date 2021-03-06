#include <SDL2/SDL.h>
#include <GameEngine/Game.h>
#include <GameEngine/Texture.h>
#include <GameEngine/Clock.h>


constexpr int windowWidth{ 400 };
constexpr int windowHeight{ 533 };
constexpr int totalPlatforms{ 10 };


int main(int argv, char** argc)
{
    GameEngine::Game geGame{ "Doodle Game!", windowWidth, windowHeight };

    geGame.isRendererVSYNC = true; //limit framerate to 60
    geGame.isCountingFrames = true;

    geGame.init();

    GameEngine::Texture txBackground, txPlatform, txDoodle;

    txBackground.loadFromFile("resources/images/background.png");
    txPlatform.loadFromFile("resources/images/platform.png");
    txDoodle.loadFromFile("resources/images/doodle.png");

    SDL_Point plat[totalPlatforms];

    for (int i = 0; i < totalPlatforms; i++) {
        plat[i].x = GameEngine::Game::randomInt(0, windowWidth);
        plat[i].y = GameEngine::Game::randomInt(0, windowHeight);
    }

    int x = 100;
    int y = 100;
    int h = 200;
    float dx = 0;
    float dy = 0;
    bool isRunning{ true };
    SDL_Event event;
    int framesCounted{ 0 };

    //GameEngine::Clock frameCoutner;

    while (isRunning)
    {
     /*   float avgFPS{ static_cast<float>(framesCounted) / frameCoutner.elapsedInSeconds() };
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }

        SDL_Log("Frames per sec: %f", avgFPS);*/

        SDL_Log("Frames per sec from game obj: %f", geGame.getAvgFPS());

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
            /*case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    x -= 3;
                    break;
                case SDLK_RIGHT:
                    x += 3;
                    break;
                default:
                    break;
                }*/
            }
        }

        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_RIGHT]) x += 3;
        if (state[SDL_SCANCODE_LEFT]) x -= 3;

        dy += 0.2f;
        y += static_cast<int>(dy);

        if (y > 500) dy = -10;

        if (y < h) {
            for (int i = 0; i < totalPlatforms; i++) {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > windowHeight) {
                    plat[i].y = 0;
                    plat[i].x = GameEngine::Game::randomInt(0, windowWidth); //rand() % 400;
                }
            }
        }

        //possible collision detection
        for (int i = 0; i < totalPlatforms; i++) {
            if (
                (x + 50 > plat[i].x) &&
                (x + 20 < plat[i].x + 68) &&
                (y + 70 > plat[i].y) &&
                (y + 70 < plat[i].y + 14) &&
                (dy > 0)
             )
                dy = -10;
        }

        //Clear screen with background image!!!
        txBackground.render();
        txDoodle.render(x, y);

        for (int i = 0; i < totalPlatforms; i++) {
            //tx.setPosition(plat[i].x, plat[i].y);
            //app.draw(sPlat);
            txPlatform.render(plat[i].x, plat[i].y);
        }

        geGame.updateScreen();
        framesCounted++;
    }

    return 0;
}
