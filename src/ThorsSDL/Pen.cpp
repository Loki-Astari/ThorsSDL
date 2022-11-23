#include "Pen.h"
#include "Window.h"


using namespace ThorsAnvil::UI;

Pen const& Pen::drawPoint(Window& window, Pt const& point) const
{
    SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoint(window.getSurface(), point.x, point.y);
    return *this;
}

Pen const& Pen::drawLine(Window& window, Pt const& start, Pt const& end) const
{
    SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLine(window.getSurface(), start.x, start.y, end.x, end.y);
    return *this;
}

Pen const& Pen::drawRect(Window& window, Rect const& rect) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(window.getSurface(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRect(window.getSurface(), &rect);
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRect(window.getSurface(), &rect);
    }
    return *this;
}

Pen const& Pen::drawPoints(Window& window, std::initializer_list<Pt> points) const
{
    SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoints(window.getSurface(), std::data(points), std::size(points));
    return *this;
}

Pen const& Pen::drawLines(Window& window, std::initializer_list<Pt> lines) const
{
    SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLines(window.getSurface(), std::data(lines), std::size(lines));
    return *this;
}

Pen const& Pen::drawRects(Window& window, std::initializer_list<Rect> rects) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(window.getSurface(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRects(window.getSurface(), std::data(rects), std::size(rects));
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(window.getSurface(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRects(window.getSurface(), std::data(rects), std::size(rects));
    }

    return *this;
}
