#include "Pen.h"
#include "DrawContext.h"


using namespace ThorsAnvil::UI;

Pen::Pen(Color ink, Color fill)
    : ink(ink)
    , fill(fill)
{}

void Pen::drawPoint(DrawContext& drawContext, Pt const& point) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoint(drawContext.getSurface(), point.x, point.y);
}

void Pen::drawLine(DrawContext& drawContext, Pt const& start, Pt const& end) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLine(drawContext.getSurface(), start.x, start.y, end.x, end.y);
}

void Pen::drawRect(DrawContext& drawContext, Rect const& rect) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(drawContext.getSurface(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRect(drawContext.getSurface(), &rect);
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRect(drawContext.getSurface(), &rect);
    }
}

void Pen::drawPoints(DrawContext& drawContext, std::initializer_list<Pt> points) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoints(drawContext.getSurface(), std::data(points), std::size(points));
}

void Pen::drawLines(DrawContext& drawContext, std::initializer_list<Pt> lines) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLines(drawContext.getSurface(), std::data(lines), std::size(lines));
}

void Pen::drawRects(DrawContext& drawContext, std::initializer_list<Rect> rects) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(drawContext.getSurface(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRects(drawContext.getSurface(), std::data(rects), std::size(rects));
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRects(drawContext.getSurface(), std::data(rects), std::size(rects));
    }
}

Texture::Texture(DrawContext& drawContext, SDL_Surface& surface)
    : drawContext(drawContext)
    , texture(SDL_CreateTextureFromSurface(drawContext.getSurface(), &surface), [](SDL_Texture* t){if (t){SDL_DestroyTexture(t);}})
{
    if (!texture)
    {
        throw std::runtime_error("Failed to Create Texture");
    }
}

void Texture::doDraw(Rect dst, Rect src)
{
    Rect*    rectSrc = &src;
    if (src.w == 0 || src.h == 0)
    {
        rectSrc = nullptr;
    }
    if (dst.w == 0 || dst.h == 0)
    {
        SDL_QueryTexture(texture.get(), nullptr, nullptr, &dst.w, &dst.h);
    }
    SDL_RenderCopy(drawContext.getSurface(), texture.get(), rectSrc, &dst);
}


TextPen::TextPen(std::string const& fontName, int pt, Color ink, Color fill)
    : Pen(ink, fill)
    // Note: I know I don't need to test for null on p here.
    //       But doing so makes the unit tests easier to write.
    //       We check that a failed Open() does not result in a call to Close().
    , font(TTF_OpenFont(fontName.c_str(), pt), [](TTF_Font* p){if (p){TTF_CloseFont(p);}})
{
    if (!font)
    {
        throw std::runtime_error("Failed to create font");
    }
}

// Note only use in: TextPen::createTextureFromString
struct SurfaceHolder
{
    SDL_Surface*    surface;

    SurfaceHolder(TTF_Font& font, char const* message, Color const& ink)
        : surface(TTF_RenderText_Solid(&font, message, SDL_Color{ink.r, ink.b, ink.g, ink.alpha}))
    {
        if (!surface)
        {
            throw std::runtime_error("Failed to Create Surface");
        }
    }
    ~SurfaceHolder()
    {
        SDL_FreeSurface(surface);
    }


    SurfaceHolder(SurfaceHolder const&)             = delete;
    SurfaceHolder& operator=(SurfaceHolder const&)  = delete;
    SurfaceHolder(SurfaceHolder&&)                  = delete;
    SurfaceHolder& operator=(SurfaceHolder&&)       = delete;
};


Texture TextPen::createTextureFromString(DrawContext& drawContext, char const* message) const
{
    SurfaceHolder       surface(*font, message, ink);
    return Texture{drawContext, *surface.surface};
}
