#include "Pen.h"
#include "DrawContext.h"


using namespace ThorsAnvil::UI;

Pen const& Pen::drawPoint(DrawContext& drawContext, Pt const& point) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoint(drawContext.getSurface(), point.x, point.y);
    return *this;
}

Pen const& Pen::drawLine(DrawContext& drawContext, Pt const& start, Pt const& end) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLine(drawContext.getSurface(), start.x, start.y, end.x, end.y);
    return *this;
}

Pen const& Pen::drawRect(DrawContext& drawContext, Rect const& rect) const
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
    return *this;
}

Pen const& Pen::drawPoints(DrawContext& drawContext, std::initializer_list<Pt> points) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoints(drawContext.getSurface(), std::data(points), std::size(points));
    return *this;
}

Pen const& Pen::drawLines(DrawContext& drawContext, std::initializer_list<Pt> lines) const
{
    SDL_SetRenderDrawColor(drawContext.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLines(drawContext.getSurface(), std::data(lines), std::size(lines));
    return *this;
}

Pen const& Pen::drawRects(DrawContext& drawContext, std::initializer_list<Rect> rects) const
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

    return *this;
}
