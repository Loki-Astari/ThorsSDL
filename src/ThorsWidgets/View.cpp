#include "View.h"

using namespace ThorsAnvil::Widgets;

View::View(UI::Window& window, Layout& layout, Theme& theme)
    : WidgetView(*this, layout)
    , UI::View(window)
    , theme(theme)
    , size{0, 0}
{}

void View::tile()
{
    UI::DrawContext&    context = getDrawContext();
    size = preferredLayout(context, theme);
    size.x += 4;
    size.y += 4;
    performLayout({2,2}, theme);
}

void View::draw(UI::DrawContext& context)
{
    drawWidget(context, theme);
}

UI::Sz View::reset()
{
    return size;
}

void View::handleEventWindowEnter(SDL_WindowEvent const& /*event*/)
{
    handleEventMouseMoveEnterWidget();
}

void View::handleEventWindowLeave(SDL_WindowEvent const& /*event*/)
{
    handleEventMouseMoveLeaveWidget();
}

void View::handleEventMouseMove(SDL_MouseMotionEvent const& event)
{
    handleEventMouseMoveInWidget(event);
}

void View::handleEventMouseDown(SDL_MouseButtonEvent const& /*event*/)
{
    mouseDownIn = handleEventMouseDownInWidget();
}

void View::handleEventMouseUp(SDL_MouseButtonEvent const& /*event*/)
{
    mouseDownIn = handleEventMouseUpInWidget(mouseDownIn);
    if (mouseDownIn)
    {
        mouseDownIn->handleEventMouseUpOutsideWidget();
        mouseDownIn = nullptr;
    }
}
