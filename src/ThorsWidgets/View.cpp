#include "View.h"
#include "ThorsUI/Window.h"

using namespace ThorsAnvil::Widgets;

View::View(UI::Window& window, Layout& layout, Theme& theme, UI::Sz minSize, HorzAlign hAlign, VertAlign vAlign)
    : WidgetView(layout)
    , UI::View(window)
    , theme(theme)
    , minSize(minSize)
    , hAlign(hAlign)
    , vAlign(vAlign)
{}

UI::Sz View::tile(bool fitWindowToView)
{
    UI::DrawContext&    context = getDrawContext();
    UI::Sz size = preferredLayout(context, theme);

    size.x += theme.windowPadding * 2;
    size.y += theme.windowPadding * 2;
    size.x = std::max(size.x, minSize.x);
    size.y = std::max(size.y, minSize.y);


    UI::Sz windowSize;
    if (fitWindowToView)
    {
        windowSize = size;
    }
    else
    {
        windowSize = parent.getSize();
    }
    int xOffset;
    int yOffset;
    switch (hAlign)
    {
        case Left:      xOffset = theme.windowPadding;break;
        case Middle:    xOffset = (windowSize.x - size.x) / 2 + theme.windowPadding;break;
        case Right:     xOffset = windowSize.x - size.x + theme.windowPadding;break;
    }
    switch (vAlign)
    {
        case Top:       yOffset = theme.windowPadding;break;
        case Center:    yOffset = (windowSize.y - size.y) / 2 + theme.windowPadding;break;
        case Bottom:    yOffset = windowSize.y - size.y + theme.windowPadding;break;
    }
    performLayout({xOffset ,yOffset}, theme);

    return size;
}

void View::draw(UI::DrawContext& context)
{
    drawWidget(context, theme);
}

UI::Sz View::reset(bool fitWindowToView)
{
    UI::Sz size = tile(fitWindowToView);
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
