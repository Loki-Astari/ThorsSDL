#include "WidgetExample.h"
#include "WidgetView.h"
#include "ThorsSDL/Pen.h"

using namespace ThorsAnvil::Widgets;


WidgetExample::WidgetExample(WidgetView& parent)
    : Widget(parent)
{}

WidgetExample::~WidgetExample()
{}

void WidgetExample::drawWidget(UI::DrawContext& drawContext, Theme const& /*theme*/)
{
    ThorsAnvil::UI::Pen     red{ThorsAnvil::UI::C::red};
    red.drawRect(drawContext, {topLeft.x, topLeft.y, 20, 20});
}

ThorsAnvil::UI::Sz WidgetExample::preferredLayout(Theme const& /*theme*/)
{
    return {20, 20};
}

void WidgetExample::performLayout(UI::Pt tl, Theme const& /*theme*/)
{
    topLeft = tl;
}
