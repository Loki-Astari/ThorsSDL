#include "WidgetButton.h"
#include "Theme.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;

WidgetButton::WidgetButton(WidgetView& parent, std::string const& text,
                           ButtonAction&& action,
                           UI::Sz minSize, bool visible)
    : WidgetLabel(parent, text, minSize, visible)
    , action(std::move(action))
{}

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
    WidgetLabel::drawWidget(drawContext, theme);
}

void WidgetButton::handleEventMouseMoveEnterWidget()
{
    state = state == DownOutside ? Down : Hover;
}
void WidgetButton::handleEventMouseMoveLeaveWidget()
{
    state = state == Down ? DownOutside : Up;
}

UI::TextPen const& WidgetButton::getTextPen(Theme const& theme)
{
    switch (state)
    {
        case Up:            return theme.normalTextPen;
        case DownOutside:   return theme.normalTextPen;
        case Hover:         return theme.hoverTextPen;
        case Down:          return theme.pressTextPen;
    }
    return theme.normalTextPen;
}

Widget* WidgetButton::handleEventMouseDownInWidget()
{
    state = Down;
    return this;
}

Widget* WidgetButton::handleEventMouseUpInWidget(Widget* mouseDownIn)
{
    if (mouseDownIn != this) {
        return mouseDownIn;
    }
    state = Up;
    action();
    return nullptr;
}

void WidgetButton::handleEventMouseUpOutsideWidget()
{
    state = Up;
}
