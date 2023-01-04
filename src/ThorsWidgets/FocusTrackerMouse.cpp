#include "FocusTrackerMouse.h"
#include "FocusTrackerKeyboard.h"
#include "Widget.h"

using namespace ThorsAnvil::Widgets;

FocusTrackerMouse::FocusTrackerMouse()
    : mouseOver(none())
    , mouseDownIn(none())
{}

void FocusTrackerMouse::addInterface(WidgetMouseFocusInterface& interface)
{
    mouseInputWidgets.emplace_back(&interface);
}

void FocusTrackerMouse::remInterface(WidgetMouseFocusInterface& interface)
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

void FocusTrackerMouse::handleEventMouseMoveEnterWidget(SDL_WindowEvent const& /*event*/)
{
    if (isValid(mouseOver)) {
        (*mouseOver)->handleEventMouseMoveEnterWidget();
    }
}

void FocusTrackerMouse::handleEventMouseMoveLeaveWidget(SDL_WindowEvent const& /*event*/)
{
    if (isValid(mouseOver)) {
        (*mouseOver)->handleEventMouseMoveLeaveWidget();
    }
    mouseOver = none();
}

void FocusTrackerMouse::handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event)
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

void FocusTrackerMouse::handleEventMouseDownInWidget(SDL_MouseButtonEvent const& /*event*/)
{
    mouseDownIn = none();
    if (isValid(mouseOver))
    {
        mouseDownIn = mouseOver;
        (*mouseDownIn)->handleEventMouseDownInWidget();
    }
}

void FocusTrackerMouse::handleEventMouseUpInWidget(SDL_MouseButtonEvent const& /*event*/)
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
