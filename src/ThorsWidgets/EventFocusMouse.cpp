#include "EventFocusMouse.h"
#include "EventFocusKeyboard.h"
#include "Widget.h"

using namespace ThorsAnvil::Widgets;

EventFocusMouse::EventFocusMouse()
    : mouseOver(none())
    , mouseDownIn(none())
{}

void EventFocusMouse::addInterface(WidgetMouseFocusInterface& interface)
{
    mouseInputWidgets.emplace_back(&interface);
}

void EventFocusMouse::remInterface(WidgetMouseFocusInterface& interface)
{
    auto find = std::find(std::cbegin(mouseInputWidgets), std::cend(mouseInputWidgets), &interface);
    if (find != none())
    {
        if (find == mouseDownIn)
        {
            (*mouseDownIn)->handleEventMouseUpOutsideWidget();
            mouseDownIn = none();
        }
        if (find != mouseOver)
        {
            (*mouseOver)->handleEventMouseMoveLeaveWidget();
            mouseOver = none();
        }
        mouseInputWidgets.erase(find);
    }
}

void EventFocusMouse::handleEventMouseMoveEnterWidget(SDL_WindowEvent const& /*event*/)
{
    if (isValid(mouseOver)) {
        (*mouseOver)->handleEventMouseMoveEnterWidget();
    }
}

void EventFocusMouse::handleEventMouseMoveLeaveWidget(SDL_WindowEvent const& /*event*/)
{
    if (isValid(mouseOver)) {
        (*mouseOver)->handleEventMouseMoveLeaveWidget();
    }
    mouseOver = none();
}

void EventFocusMouse::handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event)
{
    UI::Pt  mousePosition = {event.x, event.y};
    if (isValid(mouseOver))
    {
        UI::Rect const& rect = (*mouseOver)->getRect();

        if (rect.contains(mousePosition))
        {
            (*mouseOver)->handleEventMouseMoveInWidget();
            return;
        }
        else
        {
            (*mouseOver)->handleEventMouseMoveLeaveWidget();
        }
    }
    mouseOver = none();
    for (auto loop = std::cbegin(mouseInputWidgets); loop != std::cend(mouseInputWidgets); ++loop)
    {
        UI::Rect const& rect = (*loop)->getRect();
        if ((*loop)->isVisible() && rect.contains(mousePosition))
        {
            mouseOver = loop;
            (*mouseOver)->handleEventMouseMoveEnterWidget();
            break;
        }
    }
}

void EventFocusMouse::handleEventMouseDownInWidget(SDL_MouseButtonEvent const& /*event*/)
{
    mouseDownIn = none();
    if (isValid(mouseOver))
    {
        mouseDownIn = mouseOver;
        (*mouseDownIn)->handleEventMouseDownInWidget();
    }
}

void EventFocusMouse::handleEventMouseUpInWidget(SDL_MouseButtonEvent const& /*event*/)
{
    if (!isValid(mouseDownIn)) {
        return;
    }

    if (mouseDownIn == mouseOver) {
        (*mouseDownIn)->handleEventMouseUpInWidget();
    }
    else {
        (*mouseDownIn)->handleEventMouseUpOutsideWidget();
    }
    mouseDownIn = none();
}
