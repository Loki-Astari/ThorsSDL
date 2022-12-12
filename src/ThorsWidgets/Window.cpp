#include "Window.h"

using namespace ThorsAnvil::Widgets;

Window::Window(UI::Window& window, Layout& layout, Theme& theme)
    : WidgetView(*this, layout)
    , View(window)
    , theme(theme)
    , size{0, 0}
{}

void Window::tile()
{
    UI::DrawContext&    context = getDrawContext();
    size = preferredLayout(context, theme);
    size.x += 4;
    size.y += 4;
    performLayout({2,2}, theme);
}

void Window::draw(UI::DrawContext& context)
{
    drawWidget(context, theme);
}

UI::Sz Window::reset()
{
    return size;
}

void Window::handleEventWindowEnter(SDL_WindowEvent const& /*event*/)
{
    handleEventMouseMoveEnterWidget();
}

void Window::handleEventWindowLeave(SDL_WindowEvent const& /*event*/)
{
    handleEventMouseMoveLeaveWidget();
}

void Window::handleEventMouseMove(SDL_MouseMotionEvent const& event)
{
    WidgetView::handleEventMouseMoveInWidget(event);
}
