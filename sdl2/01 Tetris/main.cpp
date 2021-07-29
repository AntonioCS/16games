//#include <ctime>
//#include <SFML/Graphics.hpp>
//using namespace sf;

#include <string>
#include <SDL2/SDL.h>
#include <GameEngine/Game.h>
#include <GameEngine/Texture.h>
#include <GameEngine/Clock.h>
#include <GameEngine/ColorList.h>

//#include <Game.h>

constexpr int M{ 20 };
constexpr int N{ 10 };

int field[M][N] = {0};

constexpr int BufferSize{ 4 };

SDL_Point figuresBufferA[BufferSize] {0};
SDL_Point figuresBufferB[BufferSize] {0};

constexpr int figures[7][4] =
{
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

constexpr int tileMeasurement{ 18 };

#define BufferLoop for (int i{0}; i < BufferSize; i++)

bool checkIfTileAllowedToContinue()
{
    BufferLoop {
        if (figuresBufferA[i].x < 0 || figuresBufferA[i].x >= N || figuresBufferA[i].y >= M) {
            return false;
        }
        if (field[figuresBufferA[i].y][figuresBufferA[i].x] != 0) {
            return false;
        }
    }

    return true;
}


int main(int argv, char** argc)
{  
    GameEngine::Game geGame{ "The Game!", 320, 480};

    geGame.init();

    GameEngine::Texture tiles, background, frame;
    tiles.loadFromFile("resources/images/tiles.png");
    background.loadFromFile("resources/images/background.png");
    frame.loadFromFile("resources/images/frame.png");

    int dx{ 0 };
    bool rotate{ false };
    int colorNum{ 1 };
    float timer{ 0 };
    float delay{ 0.3f };

    bool isRunning{ true };
    
    GameEngine::Clock clock;
   
    SDL_Event event;
    while (isRunning)
    {
        timer += clock.elapsedInSeconds();        
        clock.reset();

        while (SDL_PollEvent(&event)) {
            switch(event.type)
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
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            rotate = true;
                            break;
                        case SDLK_LEFT:
                            dx = -1;
                            break;
                        case SDLK_RIGHT:
                            dx = 1;
                            break;
                        //case SDLK_DOWN:
                        //    break;
                        default:
                            break;
                    }
                break;
                default:
                    ;
            }
        }


        //if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05f;

        //// <- Move -> ///
        BufferLoop{
            figuresBufferB[i] = figuresBufferA[i];
            figuresBufferA[i].x += dx;
        }

        if (!checkIfTileAllowedToContinue()) {
            BufferLoop
                figuresBufferA[i] = figuresBufferB[i];
        }

        //////Rotate//////
        if (rotate) {
            const SDL_Point p = figuresBufferA[1]; //center of rotation

            BufferLoop {
                const int x{ figuresBufferA[i].y - p.y };
                const int y{ figuresBufferA[i].x - p.x };
                figuresBufferA[i].x = p.x - x;
                figuresBufferA[i].y = p.y + y;
            }
            if (!checkIfTileAllowedToContinue()) {
                BufferLoop
                    figuresBufferA[i] = figuresBufferB[i];
            }
        }

        ///////Tick//////
        if (timer > delay)
        {
            //SDL_Log("TICK!!! %f --- %f", timer, delay);
            BufferLoop {
                figuresBufferB[i] = figuresBufferA[i];
                figuresBufferA[i].y++;// += 1;
            }

            if (!checkIfTileAllowedToContinue()) {
                BufferLoop {
                    field[figuresBufferB[i].y][figuresBufferB[i].x] = colorNum;
                }

                colorNum = 1 + GameEngine::Game::randomInt(1, 7);                
                const int n{ GameEngine::Game::randomInt(1, 7) };

                BufferLoop {
                    figuresBufferA[i].x = figures[n][i] % 2;
                    figuresBufferA[i].y = figures[n][i] / 2;
                }
            }
            timer = 0;
        }

        ///////check lines//////////
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }
            if (count < N)
                k--;
        }

        dx = 0;
        rotate = false;
        delay = 0.3f;

        /////////draw//////////
        geGame.clear(GameEngine::ColorList::black);        
        background.render();

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (field[i][j] == 0)
                    continue;

                SDL_Rect theTile{ field[i][j] * tileMeasurement, 0, tileMeasurement, tileMeasurement };
                tiles.render((j * 18) + 28, (i * 18) + 31, &theTile);
            }
        }
        
        BufferLoop {

            SDL_Rect theTile{ colorNum * tileMeasurement, 0, tileMeasurement, tileMeasurement };
            tiles.render(
                figuresBufferA[i].x * 18 + 28,
                figuresBufferA[i].y * 18 + 31,
                &theTile
            );
        }


        frame.render();
        geGame.updateScreen();
    }

    return 0;
}
