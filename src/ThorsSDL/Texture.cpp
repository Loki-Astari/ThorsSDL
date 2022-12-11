#include "Texture.h"
#include "DrawContext.h"


using namespace ThorsAnvil::UI;

Texture::Texture()
    : drawContext(nullptr)
{}

Texture::Texture(DrawContext& drawContext, SDL_Surface& surface)
    : drawContext(&drawContext)
    , texture(SDL_CreateTextureFromSurface(drawContext.getRenderer(), &surface), [](SDL_Texture* t){if (t){SDL_DestroyTexture(t);}})
{
    if (!texture) {
        throw std::runtime_error("Failed to Create Texture");
    }
}

Sz Texture::size() const
{
    Sz  size{0, 0};
    if (drawContext && texture) {
        SDL_QueryTexture(texture.get(), nullptr, nullptr, &size.x, &size.y);
    }
    return size;
}

void Texture::draw(Rect dst, Rect src) const
{
    if (drawContext && texture)
    {
        Rect*    rectSrc = &src;
        if (src.w == 0 || src.h == 0) {
            rectSrc = nullptr;
        }
        if (dst.w == 0 || dst.h == 0) {
            SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
        }
        SDL_RenderCopy(drawContext->getRenderer(), texture.get(), rectSrc, &dst);
    }
}
