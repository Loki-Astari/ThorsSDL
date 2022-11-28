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

TextPen::TextPen(std::string const& fontName, int pt, Color ink, Color fill)
    : Pen(ink, fill)
    , font(TTF_OpenFont(fontName.c_str(), pt), [](TTF_Font* p){TTF_CloseFont(p);})
{
    if (!font)
    {
        throw std::runtime_error("Failed to create font");
    }
}
