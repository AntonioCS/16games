#include <GameEngine/UsesRenderer.h>
#include <stdexcept>

namespace GameEngine
{
    SDL_Renderer* UsesRenderer::renderer{nullptr};

    SDL_Renderer* UsesRenderer::getRenderer()
    {
        if (renderer == nullptr)
            throw std::runtime_error{ "Renderer is not set" };

        return renderer;
    }
}
