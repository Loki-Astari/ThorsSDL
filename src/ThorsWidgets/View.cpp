#include "View.h"
#include "ThorsUI/Window.h"

using namespace ThorsAnvil::Widgets;

View::View(UI::Window& window, Layout& layout, Theme& theme)
    : WidgetView(layout)
    , UI::View(window)
    , theme(theme)
    , size{0, 0}
{}

void View::tile(HorzAlign hAlign, VertAlign vAlign)
{
    UI::DrawContext&    context = getDrawContext();
    size = preferredLayout(context, theme);
    size.x += 4;
    size.y += 4;

    UI::Sz windowSize = parent.getSize();
    int xOffset;
    int yOffset;
    switch (hAlign)
    {
        case Left:      xOffset = 2;break;
        case Middle:    xOffset = (windowSize.x - size.x) / 2;break;
        case Right:     xOffset = windowSize.x - size.x + 2;break;
    }
    switch (vAlign)
    {
        case Top:       yOffset = 2;break;
        case Center:    yOffset = (windowSize.y - size.y) / 2;break;
        case Bottom:    yOffset = windowSize.y - size.y + 2;break;
    }

    performLayout({xOffset ,yOffset}, theme);
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
