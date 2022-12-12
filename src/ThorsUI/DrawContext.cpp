#include "DrawContext.h"

using namespace ThorsAnvil::UI;

DrawContext::DrawContext(SDL_Window* sdlWindow, RenderState const& renState)
    : renderer(sdlWindow ? std::make_unique<SDL::Renderer>(sdlWindow, renState): nullptr)
{}

DrawContext::~DrawContext()
{}

DrawContext::DrawContext(DrawContext&& move) noexcept
{
    renderer = std::exchange(move.renderer, nullptr);
}

DrawContext& DrawContext::operator=(DrawContext&& move) noexcept
{
    renderer = std::exchange(move.renderer, nullptr);
    return *this;
}
