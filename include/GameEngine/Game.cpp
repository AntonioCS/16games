#include <random>
#include <stdexcept>
#include <unordered_map>
#include <GameEngine/Game.h>
#include <GameEngine/Texture.h>
#include <GameEngine/Color.h>
#include <SDL2/SDL_image.h>


namespace GameEngine {
    Game::Game(std::string&& title, int w, int h) : m_title(title), m_w(w), m_h(h)
    {
        
    }

    void Game::init()
    {
        if (m_window != nullptr || m_renderer != nullptr)
            throw std::runtime_error{ "Game already initialized" };

        if (SDL_Init(SDL_INIT_VIDEO) == 0) {
            m_window = SDL_CreateWindow(m_title.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_w, m_h,
                createWindowFlags()
            );

            m_renderer = SDL_CreateRenderer(
                m_window, -1,
                createRendererFlags()
                //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );

            if (const int imgFlags{ IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF };
                !(IMG_Init(imgFlags) & imgFlags)) {
                throw std::runtime_error{ "Unable to initialize SDL_image: " + std::string{IMG_GetError()} };
            }

            UsesRenderer::renderer = m_renderer;
        }
        else {
            throw std::runtime_error{ "Unable to initialize SDL2: " + std::string{SDL_GetError()} };
        }
    }

    Game::~Game()
    {
        UsesRenderer::renderer = nullptr;

        if (m_renderer) SDL_DestroyRenderer(m_renderer);
        if (m_window) SDL_DestroyWindow(m_window);

        IMG_Quit();
        SDL_Quit();
    }

    void Game::clear(const Color& color) const
    {
        Uint8 r, g, b, a;
        const bool reApplySavedColor{ SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a) == 0 };

        SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(m_renderer);

        if (reApplySavedColor) {
            SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        }
    }

    void Game::updateScreen() const
    {        
        SDL_RenderPresent(m_renderer);
    }

    //https://stackoverflow.com/a/13445752/8715
    //https://stackoverflow.com/questions/7114043/random-number-generation-in-c11-how-to-generate-how-does-it-work
    int Game::randomInt(int min, int max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        const std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [1, 6]

        return dist(rng);
    }

    float Game::randomFloat(float min, float max)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        const std::uniform_real_distribution<float> dist(min, max); // distribution in range [1, 6]

        return dist(rng);
    }


    namespace 
    {
        uint32_t flagsCreator(const std::unordered_map<uint32_t, bool>& theFlagsTable)
        {
            uint32_t flags{ 0 };
            for (const auto &[flag, state] : theFlagsTable)
            {
                if (state) {
                    flags |= flag;
                }
            }

            return flags;
        }
    }

    uint32_t Game::createWindowFlags() const
    {
        const std::unordered_map<uint32_t, bool> theFlagsTable{
            { SDL_WINDOW_FULLSCREEN, isWindowFullscreen },
            { SDL_WINDOW_FULLSCREEN_DESKTOP, isWindowFullscreenDesktop },
            { SDL_WINDOW_OPENGL, isWindowOpengl },
            { SDL_WINDOW_VULKAN, isWindowVulkan },
            { SDL_WINDOW_METAL, isWindowMetal },
            { SDL_WINDOW_HIDDEN, isWindowHidden },
            { SDL_WINDOW_BORDERLESS, isWindowBorderless },
            { SDL_WINDOW_RESIZABLE, isWindowResizable },
            { SDL_WINDOW_MINIMIZED, isWindowMinimized },
            { SDL_WINDOW_MAXIMIZED, isWindowMaximized },
            { SDL_WINDOW_INPUT_GRABBED, isWindowInputGrabbed },
            { SDL_WINDOW_ALLOW_HIGHDPI, isWindowAllowHighdpi },
        };

        return flagsCreator(theFlagsTable);
    }

    uint32_t Game::createRendererFlags() const
    {
        const std::unordered_map<uint32_t, bool> theFlagsTable{
            { SDL_RENDERER_SOFTWARE, isRendererSoftware },
            { SDL_RENDERER_ACCELERATED, isRendererAccelerated },
            { SDL_RENDERER_PRESENTVSYNC, isRendererVSYNC },
            { SDL_RENDERER_TARGETTEXTURE, isRendererTargetTexture }
        };

        return flagsCreator(theFlagsTable);
    }
}
