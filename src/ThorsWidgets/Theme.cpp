#include "Theme.h"
#include "WidgetView.h"
#include "WidgetLabel.h"
#include "WidgetButton.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;

// By default we don't draw anything for a view.
void Theme::drawWidget(UI::DrawContext&, WidgetView const&) const
{}

void Theme::drawWidget(UI::DrawContext&, WidgetLabel const& label) const
{
    UI::Pt point = label.getDrawPosition();
    UI::Sz size  = label.getDrawSize();
    label.centerText(*this, point, size);

    label.texture.draw({point.x, point.y, size.x, size.y});
}

void Theme::drawWidget(UI::DrawContext& drawContext, WidgetButton const& button) const
{
    UI::Pt          point   = button.getDrawPosition();
    UI::Sz          size    = button.getDrawSize();
    UI::Pen const&  pen     = button.state != Down ? buttonBorderPen : buttonPressedPen;

    pen.drawRect(drawContext, {point.x, point.y, size.x, size.y});
}
