#include "EventFocusMouse.h"
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
    auto find = std::find(std::begin(mouseInputWidgets), std::end(mouseInputWidgets), &interface);
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

void EventFocusMouse::handleEventMouseMoveInWidget(UI::Pt const& mousePosition)
{
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
    for (auto loop = std::begin(mouseInputWidgets); loop != std::end(mouseInputWidgets); ++loop)
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

void EventFocusMouse::handleEventMouseDownInWidget(SDL_MouseButtonEvent const& /*event*/, EventFocusKeyboard& /*textInputSet*/)
{
    std::cerr << "handleEventMouseDownInWidget\n";
    mouseDownIn = none();
    if (isValid(mouseOver))
    {
        mouseDownIn = mouseOver;
        std::cerr << "Sending handleEventMouseDownInWidget\n";
        (*mouseDownIn)->handleEventMouseDownInWidget();
        //textInputSet.handleEventMouseDown(*mouseDownIn);
    }
}

void EventFocusMouse::handleEventMouseUpInWidget(SDL_MouseButtonEvent const& /*event*/)
{
    std::cerr << "handleEventMouseUpInWidget\n";
    if (!isValid(mouseDownIn)) {
        return;
    }

    if (mouseDownIn == mouseOver)
    {
        std::cerr << "Sending handleEventMouseUpInWidget\n";
        (*mouseDownIn)->handleEventMouseUpInWidget();
    }
    else
    {
        std::cerr << "Sending handleEventMouseUpOutsideWidget\n";
        (*mouseDownIn)->handleEventMouseUpOutsideWidget();
    }
    mouseDownIn = none();
}
