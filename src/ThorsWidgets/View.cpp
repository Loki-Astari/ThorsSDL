#include "View.h"
#include "ThorsUI/Window.h"
#include <string_view>

using namespace ThorsAnvil::Widgets;

View::View(UI::Window& window, Layout& layout, Theme& theme, UI::Sz minSize, HorzAlign hAlign, VertAlign vAlign)
    : WidgetView(layout)
    , UI::View(window)
    , theme(theme)
    , minSize(minSize)
    , mouseDownIn(nullptr)
    , hAlign(hAlign)
    , vAlign(vAlign)
    // Force re-draw first time
    , updated(true)
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

bool View::updateState()
{
    // If we return true then a redraw will be done.
    // So set `updated` to false.
    // Now, only need to re-draw if we mark as dirty (see below).
    return std::exchange(updated, false);
}

void View::markDirty()
{
    updated = true;
}

void View::draw(UI::DrawContext& context)
{
    drawWidget(context, theme);
}

UI::Sz View::reset(bool fitWindowToView)
{
    UI::Sz size = tile(fitWindowToView);
    textInputSet.reset();
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
    if (mouseDownIn)
    {
        textInputSet.handleEventMouseDown(*mouseDownIn);
    }
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

void View::handleEventKeyDown(SDL_KeyboardEvent const& /*event*/)
{}

void View::handleEventKeyUp(SDL_KeyboardEvent const& event)
{
    textInputSet.handleEventKeyUp(event);
}

void View::handleEventTextEditting(SDL_TextEditingEvent const& event)
{
    textInputSet.handleEventTextEditting(event);
}

void View::handleEventTextInput(SDL_TextInputEvent const& event)
{
    textInputSet.handleEventTextInput(event);
}

void View::handleEventTextEditingExt(SDL_TextEditingExtEvent const& event)
{
    textInputSet.handleEventTextEditingExt(event);
}

KeyboardFocusSet& View::getInterfaceSet()
{
    return textInputSet;
}
