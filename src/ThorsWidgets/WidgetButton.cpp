#include "WidgetButton.h"
#include "Theme.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;

WidgetButton::WidgetButton(WidgetView& parent, std::string const& text,
                           ButtonAction&& action,
                           UI::Sz minSize, bool visible)
    : WidgetLabel(parent, text, minSize, visible)
    , ControleHandlerMouse(parent, [&](){return dynamic_cast<Widget&>(*this).getRect();}, [&](){return dynamic_cast<Widget&>(*this).isVisible();})
    , action(std::move(action))
{}

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

void WidgetButton::handleEventMouseMoveEnterWidget()
{
    state = state == DownOutside ? Down : Hover;
    markDirty();
}
void WidgetButton::handleEventMouseMoveLeaveWidget()
{
    state = state == Down ? DownOutside : Up;
    markDirty();
}

UI::TextPen const& WidgetButton::getTextPen(Theme const& theme)
{
    switch (state)
    {
        case Up:            return theme.butNormalTextPen;
        case DownOutside:   return theme.butNormalTextPen;
        case Hover:         return theme.butHoverTextPen;
        case Down:          return theme.butPressTextPen;
    }
}

void WidgetButton::handleEventMouseDownInWidget()
{
    state = Down;
    markDirty();
}

void WidgetButton::handleEventMouseUpInWidget()
{
    markDirty();
    state = Up;
    action();
}

void WidgetButton::handleEventMouseUpOutsideWidget()
{
    markDirty();
    state = Up;
}
