#include "WidgetExample.h"
#include "WidgetView.h"
#include "ThorsSDL/Pen.h"

using namespace ThorsAnvil::Widgets;


WidgetExample::WidgetExample(WidgetView& parent)
    : Widget(parent, {20, 20})
{}

WidgetExample::~WidgetExample()
{}

void WidgetExample::drawWidget(UI::DrawContext& drawContext, Theme const& /*theme*/)
{
    ThorsAnvil::UI::Pen         red{ThorsAnvil::UI::C::red};
    ThorsAnvil::UI::Pt const&   topLeft = getDrawPosition();
    ThorsAnvil::UI::Sz const&   size = getDrawSize();
    red.drawRect(drawContext, {topLeft.x, topLeft.y, size.x, size.y});
}
