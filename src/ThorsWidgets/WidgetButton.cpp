#include "WidgetButton.h"
#include "Theme.h"
#include "ThorsSDL/Pen.h"

using namespace ThorsAnvil::Widgets;

#if 0
UI::Sz WidgetButton::doPreferredLayout(UI::DrawContext& drawContext, Theme const& theme, UI::Sz size)
{
    UI::Sz  size = WidgetLabel::doPreferredLayout(drawContext, theme, size);
    return size;
}
#endif

UI::Sz WidgetButton::addOffset(Theme const& theme, UI::Sz size) const
{
    size.x += theme.buttonBorder.x + theme.buttonBorder.w + theme.buttonPadding.x + theme.buttonPadding.w + 2 * theme.buttonLineWidth;
    size.y += theme.buttonBorder.y + theme.buttonBorder.h + theme.buttonPadding.y + theme.buttonPadding.h + 2 * theme.buttonLineWidth;
    return size;
}

void WidgetButton::centerText(Theme const& theme, UI::Pt& topLeft, UI::Sz& size) const
{
    topLeft.x += theme.labelBorder.x + theme.buttonLineWidth + theme.buttonPadding.x;
    topLeft.y += theme.labelBorder.y + theme.buttonLineWidth + theme.buttonPadding.y;

    size.x    -= (theme.labelBorder.x + theme.labelBorder.w + theme.buttonPadding.x + theme.buttonPadding.w + 2 * theme.buttonLineWidth);
    size.y    -= (theme.labelBorder.y + theme.labelBorder.h + theme.buttonPadding.y + theme.buttonPadding.h + 2 * theme.buttonLineWidth);
}

void WidgetButton::drawWidget(UI::DrawContext& drawContext, Theme const& theme)
{
    theme.drawWidget(drawContext, *this);
}
