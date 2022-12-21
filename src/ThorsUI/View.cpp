#include "View.h"
#include "Window.h"

using namespace ThorsAnvil::UI;

View::View(Window& parent)
    : parent(parent)
{
    parent.addView(*this);
}

View::~View()
{
    parent.remView(*this);
}

bool View::updateState()
{
    // By default we will force a re-draw.
    //
    // You can make more efficient by overriding and
    // only return true if your view needs to be re-drawn
    return true;
}

Sz View::reset(bool)
{
    return {0, 0};
}

void View::draw(DrawContext& /*context*/)
{}

DrawContext& View::getDrawContext()
{
    return parent;
}
