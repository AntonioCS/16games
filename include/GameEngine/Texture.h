#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <GameEngine/UsesRenderer.h>


namespace GameEngine
{
    class Texture : public UsesRenderer
    {
        SDL_Texture* m_texture{};
        int m_width{};
        int m_height{};
    public:
        ~Texture();
        bool loadFromFile(const std::string& path);
        void render(int x = 0, int y = 0, SDL_Rect* clip = nullptr) const;
    };
}
