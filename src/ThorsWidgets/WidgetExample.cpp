#include "WidgetExample.h"
#include "WidgetView.h"
#include "ThorsUI/Pen.h"

using namespace ThorsAnvil::Widgets;


WidgetExample::WidgetExample(WidgetView& parent)
    : Widget(parent, {20, 20})
{}

WidgetExample::~WidgetExample()
{}

void WidgetExample::drawWidget(UI::DrawContext& drawContext, Theme const& /*theme*/)
{
    UI::Pen         red{UI::C::red};
    UI::Pt const&   topLeft = getDrawPosition();
    UI::Sz const&   size = getDrawSize();

    red.drawRect(drawContext, {topLeft.x, topLeft.y, size.x, size.y});
}
