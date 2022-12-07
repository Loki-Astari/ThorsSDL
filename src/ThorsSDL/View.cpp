#include "View.h"

using namespace ThorsAnvil::UI;


View::~View()
{}

void View::updateState()
{}

Sz View::reset()
{
    return {0, 0};
}

void View::draw(DrawContext& /*context*/)
{}
