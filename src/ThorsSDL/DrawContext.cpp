#include "DrawContext.h"

using namespace ThorsAnvil::UI;

DrawContext::DrawContext(SDL_Window* sdlWindow, RenderState const& renState)
    : renderer(sdlWindow != nullptr ? SDL_CreateRenderer(sdlWindow, -1, renState) : nullptr)
{
    if (sdlWindow != nullptr && renderer == nullptr)
    {
        throw std::runtime_error("Failed to create renderer");
    }
}

DrawContext::~DrawContext()
{
    destroy();
}

DrawContext::DrawContext(DrawContext&& move) noexcept
{
    renderer = std::exchange(move.renderer, nullptr);
}

DrawContext& DrawContext::operator=(DrawContext&& move) noexcept
{
    destroy();
    renderer = std::exchange(move.renderer, nullptr);
    return *this;
}

void DrawContext::destroy()
{
    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
    }
}
