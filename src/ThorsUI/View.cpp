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

void View::updateState()
{}

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
