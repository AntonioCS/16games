#include <stdexcept>
#include <GameEngine/Texture.h>
#include <SDL2/SDL_image.h>


namespace GameEngine
{
    Texture::~Texture()
    {
        if (m_texture != nullptr) {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }

    void Texture::loadFromFile(const std::string& path)
    {
        SDL_Log("Image path: %s", path.c_str());
    
        if (SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            loadedSurface != nullptr)
        {
            m_texture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface);

            if (m_texture != nullptr) {
                m_width = loadedSurface->w;
                m_height = loadedSurface->h;

                SDL_FreeSurface(loadedSurface);
            } else {
                throw std::runtime_error{ "Unable to load image: " + std::string{SDL_GetError()} };
            }
        } else {
            SDL_Log("Error loading image: %s", SDL_GetError());
            throw std::runtime_error{ "Unable create surface from image: " + std::string{SDL_GetError()} };
        }
    }

    void Texture::render(int x, int y, SDL_Rect* clip) const
    {
        if (m_texture != nullptr) {
            SDL_Rect renderQuad = { x, y, m_width, m_height };
            
            if (clip != nullptr) {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
            }

            SDL_RenderCopy(getRenderer(), m_texture, clip, &renderQuad);
        }
    }
}
