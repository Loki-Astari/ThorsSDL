#include "WidgetLabel.h"
#include "Theme.h"
#include "ThorsSDL/Pen.h"

using namespace ThorsAnvil::Widgets;

WidgetLabel::WidgetLabel(WidgetView& parent,
                         std::string const& text,
                         std::string const& font, int point,
                         UI::Color color,
                         UI::Sz minSize, bool visible)
    : Widget(parent, minSize, visible)
    , text(text)
    , font(font)
    , point(point)
    , color(color)
{}

UI::Sz WidgetLabel::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz /*size*/)
{
    static const std::string fontPath = "/System/Library/Fonts/Supplemental/";

    UI::TextPen pen(fontPath + font + ".ttf", point, color);
    texture = pen.createTextureFromString(drawContext, text);
    return addOffset(theme, texture.size());
}

UI::Sz WidgetLabel::addOffset(Theme const& theme, UI::Sz size) const
{
    size.x += theme.labelBorder.x + theme.labelBorder.w;
    size.y += theme.labelBorder.y + theme.labelBorder.h;
    return size;
}

void WidgetLabel::centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const
{
    topLeft.x += theme.labelBorder.x;
    topLeft.y += theme.labelBorder.y;

    size.x    -= (theme.labelBorder.x + theme.labelBorder.w);
    size.y    -= (theme.labelBorder.y + theme.labelBorder.h);
}

void WidgetLabel::drawWidget(UI::DrawContext& drawContext, Theme const& theme)
{
    theme.drawWidget(drawContext, *this);
}
