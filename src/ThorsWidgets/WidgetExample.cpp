#include "WidgetExample.h"
#include "WidgetView.h"

using namespace ThorsAnvil::Widgets;


WidgetExample::WidgetExample(WidgetView& parent)
    : Widget(parent)
{}

WidgetExample::~WidgetExample()
{}

void WidgetExample::draw(UI::DrawContext& /*drawContext*/)
{}

void WidgetExample::updateState()
{}

void WidgetExample::reset()
{}

ThorsAnvil::UI::Pt WidgetExample::preferredLayout(Layout const& /*layout*/) const
{
    return {0,0};
}

void WidgetExample::performLayout(Layout const& /*layout*/)
{
}
