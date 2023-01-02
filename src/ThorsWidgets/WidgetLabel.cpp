#include "WidgetLabel.h"
#include "Theme.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;

WidgetLabel::WidgetLabel(WidgetView& parent,
                         std::string const& text,
                         UI::Sz minSize, bool visible)
    : Widget(parent, minSize, visible)
    , text(text)
{}

UI::Sz WidgetLabel::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz /*size*/)
{
    texture = getTextPen(theme).createTextureFromString(drawContext, text);
    UI::Sz size{getTextPen(theme).length(text), getTextPen(theme).lineSkip()};
    return addOffset(theme, size);
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

UI::TextPen const& WidgetLabel::getTextPen(Theme const& theme)
{
    return theme.labelNormalTextPen;
}

void WidgetLabel::setValue(std::string const& labelValue)
{
    text = labelValue;
    texture = getTextPen(theme).createTextureFromString(drawContext, text);
    markDirty();
}
