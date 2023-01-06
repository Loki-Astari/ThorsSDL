#include "Pen.h"
#include "DrawContext.h"
#include <map>
#include <filesystem>


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

std::shared_ptr<SDL::TTFont> Util::getFont(std::string const& fontName, int point)
{
    using Key = std::pair<std::string, int>;
    static std::map<Key, std::weak_ptr<SDL::TTFont>>      loadedFonts;
    static const std::string fontDirs[] = {   "/Library/Fonts/"
                                            , "/System/Library/Fonts/Supplemental/"
                                            , "/System Folder/Fonts/"
                                          };

    std::shared_ptr<SDL::TTFont>    result;
    std::weak_ptr<SDL::TTFont>&     font    = loadedFonts[{fontName, point}];

    if (font.use_count() == 0)
    {
        std::filesystem::path   fontPath(fontName);
        std::string             extension = fontPath.extension() == "" ? ".ttf" : "";
        std::string             path;

        std::cerr << "Search Start:\n";
        if (fontName.size() == 0 || fontName[0] != '/')
        {
            for (auto const& testPath: fontDirs)
            {
                std::string             fullPathName = testPath + fontName + extension;
                std::cerr << "\t C: " << fullPathName << "\n";
                if (std::filesystem::exists(fullPathName))
                {
                    std::cerr << "\t\tFound\n";
                    path = testPath;
                    break;
                }
            }
        }
        std::cerr << "Loading: " << path << fontName << extension << "\n";
        result = std::make_shared<SDL::TTFont>(path + fontName + extension, point);
        font = result;
    }
    else
    {
        result = font.lock();
    }
    return result;
}

TextPen::TextPen(std::string const& fontName, int point, Color ink, Color fill)
    : Pen(ink, fill)
    , font(Util::getFont(fontName, point))
{}

Texture TextPen::createTextureFromString(DrawContext& drawContext, char const* message) const
{
    SDL::Surface       surface(TTF_RenderUTF8_Solid(*font, message, SDL_Color{ink.r, ink.b, ink.g, ink.alpha}), "Failed to Create SDL-Surface");
    return Texture{drawContext, *surface};
}
