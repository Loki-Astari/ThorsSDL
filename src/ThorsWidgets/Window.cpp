#include "Window.h"

using namespace ThorsAnvil::Widgets;

Window::Window(Layout& layout, Theme& theme)
    : WidgetView(*this, layout)
    , theme(theme)
    , size{0, 0}
{}

void Window::tile()
{
    size = preferredLayout(theme);
    size.x += 4;
    size.y += 4;
    performLayout({2,2}, theme);
}

void Window::draw(ThorsAnvil::UI::DrawContext& context)
{
    drawWidget(context, theme);
}

ThorsAnvil::UI::Sz Window::reset()
{
    return size;
}
