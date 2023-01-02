#include "Widget.h"
#include "WidgetView.h"
#include "KeyboardFocusSet.h"

using namespace ThorsAnvil::Widgets;


Widget::Widget(UI::Sz minSize, bool visible)
    : parentWidget(nullptr)
    , size{0, 0}
    , minSize(minSize)
    , lastUpdate{}
    , visible{visible}
{}

Widget::Widget(WidgetView& parentWidgetParam, UI::Sz minSize, bool visible)
    : parentWidget(&parentWidgetParam)
    , size{0, 0}
    , minSize(minSize)
    , lastUpdate{}
    , visible{visible}
{
    parentWidget->addWidget(*this);
}

Widget::~Widget()
{
    if (parentWidget) {
        parentWidget->remWidget(*this);
    }
}

void Widget::markDirty()
{
    if (parentWidget == nullptr) {
        throw std::runtime_error("Root Widget should override");
    }

    parentWidget->markDirty();
}

// Handling Layout
UI::Sz Widget::preferredLayout(UI::DrawContext& drawContext, Theme const& theme)
{
    size = doPreferredLayout(drawContext, theme, size);
    size.x = std::max(size.x, minSize.x);
    size.y = std::max(size.y, minSize.y);

    return size;
}

void Widget::performLayout(UI::Pt newTopLeft, Theme const& theme)
{
    topLeft = newTopLeft;
    doPerformLayout(newTopLeft, theme);
}

UI::Sz Widget::doPreferredLayout(UI::DrawContext& /*drawContext*/, Theme const& /*theme*/, UI::Sz size)
{
    return size;
}

void Widget::doPerformLayout(UI::Pt /*newTopLeft*/, Theme const& /*theme*/)
{}

// Handle Events
bool Widget::handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event)
{
    UI::Rect rect = getRect();

    if (!rect.contains({event.x, event.y}))
    {
        return false;
    }
    handleEventMouseMoveInWidgetAction(event);
    return true;
}

Widget* Widget::handleEventMouseUpInWidget(Widget* mouseDownIn)
{
    return mouseDownIn;
}

KeyboardFocusSet& Widget::getInterfaceSet()
{
    if (parentWidget == nullptr) {
        throw std::runtime_error("Root Widget should override");
    }

    return parentWidget->getInterfaceSet();
}

WidgetKeyboardFocusInterface::WidgetKeyboardFocusInterface(WidgetView& parentWidget, UI::Sz minSize, bool visible)
    : Widget(parentWidget, minSize, visible)
    , keyboardFocusWidgets(parentWidget.getInterfaceSet())
{
    keyboardFocusWidgets.addInterface(*this);
}

WidgetKeyboardFocusInterface::~WidgetKeyboardFocusInterface()
{
    keyboardFocusWidgets.remInterface(*this);
}
