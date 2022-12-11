#include "Theme.h"
#include "WidgetView.h"
#include "WidgetLabel.h"

using namespace ThorsAnvil::Widgets;

// By default we don't draw anything for a view.
void Theme::drawWidget(UI::DrawContext&, WidgetView const&) const
{}

void Theme::drawWidget(UI::DrawContext&, WidgetLabel const& label) const
{
    UI::Pt point = label.getDrawPosition();
    UI::Sz size  = label.getDrawSize();

    label.texture.draw({point.x, point.y, size.x, size.y});
}
