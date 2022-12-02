#include "Pen.h"
#include "DrawContext.h"


using namespace ThorsAnvil::UI;

Pen::Pen(Color ink, Color fill)
    : ink(ink)
    , fill(fill)
{}

void Pen::drawPoint(DrawContext& drawContext, Pt const& point) const
{
    SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoint(drawContext.getRenderer(), point.x, point.y);
}

void Pen::drawLine(DrawContext& drawContext, Pt const& start, Pt const& end) const
{
    SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLine(drawContext.getRenderer(), start.x, start.y, end.x, end.y);
}

void Pen::drawRect(DrawContext& drawContext, Rect const& rect) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(drawContext.getRenderer(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRect(drawContext.getRenderer(), &rect);
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRect(drawContext.getRenderer(), &rect);
    }
}

void Pen::drawPoints(DrawContext& drawContext, std::initializer_list<Pt> points) const
{
    SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawPoints(drawContext.getRenderer(), std::data(points), std::size(points));
}

void Pen::drawLines(DrawContext& drawContext, std::initializer_list<Pt> lines) const
{
    SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
    SDL_RenderDrawLines(drawContext.getRenderer(), std::data(lines), std::size(lines));
}

void Pen::drawRects(DrawContext& drawContext, std::initializer_list<Rect> rects) const
{
    if (fill.alpha != 0)
    {
        SDL_SetRenderDrawColor(drawContext.getRenderer(), fill.r, fill.g, fill.b, fill.alpha);
        SDL_RenderFillRects(drawContext.getRenderer(), std::data(rects), std::size(rects));
    }

    if (ink != fill)
    {
        SDL_SetRenderDrawColor(drawContext.getRenderer(), ink.r, ink.g, ink.b, ink.alpha);
        SDL_RenderDrawRects(drawContext.getRenderer(), std::data(rects), std::size(rects));
    }
}

TextPen::TextPen(std::string const& fileName, int point, Color ink, Color fill)
    : Pen(ink, fill)
    , font(std::make_shared<SDL::TTFont>(fileName, point))
{}

Texture TextPen::createTextureFromString(DrawContext& drawContext, char const* message) const
{
    SDL::Surface       surface(*font, message, ink);
    return Texture{drawContext, *surface};
}
