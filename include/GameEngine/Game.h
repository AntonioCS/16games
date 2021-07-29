#pragma once

#include <string>
#include <cstdint>
#include <SDL2/SDL.h>

namespace GameEngine
{
    class Color;
    class Game
    {
    public:
        bool isRendererSoftware{ false };
        bool isRendererAccelerated{ true };
        bool isRendererVSYNC{ false };
        bool isRendererTargetTexture{ false };

        bool isWindowFullscreen{ false };
        bool isWindowFullscreenDesktop{ false };
        bool isWindowOpengl{ false };
        bool isWindowVulkan{ false };
        bool isWindowMetal{ false };
        bool isWindowHidden{ false };
        bool isWindowBorderless{ false };
        bool isWindowResizable{ false };
        bool isWindowMinimized{ false };
        bool isWindowMaximized{ false };
        bool isWindowInputGrabbed{ false };
        bool isWindowAllowHighdpi{ false };

    private:
        SDL_Window* m_window{};
        SDL_Renderer* m_renderer{};

        //bool m_isRunning{ false };

        std::string m_title;
        int m_w{ 800 };
        int m_h{ 600 };
    public:
        Game(std::string&& title, int w, int h);
        void init();
        ~Game();
        void clear(const Color&) const;
        void updateScreen() const;
        static int randomInt(int min, int max);
        static float randomFloat(float min, float max);

    private:
        [[nodiscard]] uint32_t createWindowFlags() const;
        [[nodiscard]] uint32_t createRendererFlags() const;
    };

}
