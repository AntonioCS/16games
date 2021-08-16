#include <string>
#include <SDL2/SDL.h>
#include <GameEngine/Game.h>
#include <GameEngine/Texture.h>
#include <GameEngine/Clock.h>
#include <GameEngine/ColorList.h>

constexpr int windowWidth{ 520 };
constexpr int windowHeight{ 450 };
constexpr int totalBlocks{ 1000 };
constexpr int blockWidth{ 43 };
constexpr int blockHeight{ 20 };
constexpr int defaultPaddleX{ 300 };
constexpr int defaultPaddleY{ 440 };




int main(int argv, char** argc)
{
    GameEngine::Game geGame{ "Arkanoid", windowWidth, windowHeight };

    geGame.init();

    GameEngine::Texture txBackground, txBall, txPaddle, txBlock;
    txBlock.loadFromFile("resources/images/block01.png");
    txBall.loadFromFile("resources/images/ball.png");
    txPaddle.loadFromFile("resources/images/paddle.png");
    txBackground.loadFromFile("resources/images/background.png");
    //Had to recreate the image as png as I was getting an error when trying to load it
    //txBackground.loadFromFile("resources/images/background.jpg");


    SDL_Rect block[totalBlocks];

    int totalActualBlocks = 0;
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            block[totalActualBlocks].x = i * blockWidth;
            block[totalActualBlocks].y = j * blockHeight;
            block[totalActualBlocks].w = blockHeight;
            block[totalActualBlocks].h = blockHeight;
            totalActualBlocks++;
        }
    }

    float dx = 6, dy = 5;
    float x = 300, y = 300;
    int paddleX{ defaultPaddleX };
    int paddleY{ defaultPaddleY };


    bool isRunning{ true };

    SDL_Event event;
    SDL_Rect ballRect{ 0,0, 6, 6 };


    auto checkForCollisions = [&](int i)
    {
        ballRect.x += 3;
        ballRect.y += 3;

        if (SDL_HasIntersection(&ballRect, &block[i])) {
            block[i].x = -100;
            block[i].y = 0;
            dx = -dx;
        }

        ballRect.x -= 3;
        ballRect.y -= 3;
    };

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

        

        x += dx;
        for (int i = 0; i < totalActualBlocks; i++) {
            checkForCollisions(i);
            //ballRect.x += 3;
            //ballRect.y += 3;

            //if (SDL_HasIntersection(&ballRect, &block[i]))
            //{
            //    block[i].x = -100;
            //    block[i].y = 0;
            //    dx = -dx;
            //}

            //ballRect.x -= 3;
            //ballRect.y -= 3;
        }

        y += dy;
        for (int i = 0; i < totalActualBlocks; i++) {
            checkForCollisions(i);
            /*if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
            {
                block[i].setPosition(-100, 0);
                dy = -dy;
            }*/
        }

        if (x < 0 || x > 520) dx = -dx;
        if (y < 0 || y > 450) dy = -dy;

       // if (Keyboard::isKeyPressed(Keyboard::Right)) sPaddle.move(6, 0);
       // if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

        //geGame.clear(GameEngine::ColorList::black);
        /////////draw//////////

        txBackground.render();
        txPaddle.render(paddleX, paddleY);


        for (int i = 0; i < totalActualBlocks; i++) {
            txBlock.render(block[i].x, block[i].y);
            //app.draw(block[i]);
        }


        geGame.updateScreen();
    }

    return 0;
}
