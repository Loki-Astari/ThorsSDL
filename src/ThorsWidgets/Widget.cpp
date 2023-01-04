#include "Widget.h"
#include "WidgetView.h"
#include "EventFocusKeyboard.h"
#include "EventFocusMouse.h"

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

EventFocusKeyboard& Widget::getKeyboardInterfaceSet()
{
    if (parentWidget == nullptr) {
        throw std::runtime_error("Root Widget should override");
    }

    return parentWidget->getKeyboardInterfaceSet();
}

EventFocusMouse& Widget::getMouseInterfaceSet()
{
    if (parentWidget == nullptr) {
        throw std::runtime_error("Root Widget should override");
    }

    return parentWidget->getMouseInterfaceSet();
}

WidgetKeyboardFocusInterface::WidgetKeyboardFocusInterface(WidgetView& parentWidget, std::function<bool()>&& iVis)
    : keyboardFocusWidgets(parentWidget.getKeyboardInterfaceSet())
    , iVis(std::move(iVis))
{
    keyboardFocusWidgets.addInterface(*this);
}

WidgetKeyboardFocusInterface::~WidgetKeyboardFocusInterface()
{
    keyboardFocusWidgets.remInterface(*this);
}

WidgetMouseFocusInterface::WidgetMouseFocusInterface(WidgetView& parentWidget, std::function<UI::Rect()>&& gRect, std::function<bool()>&& iVis)
    : mouseFocusWidgets(parentWidget.getMouseInterfaceSet())
    , gRect(std::move(gRect))
    , iVis(std::move(iVis))
{
    mouseFocusWidgets.addInterface(*this);
}
WidgetMouseFocusInterface::~WidgetMouseFocusInterface()
{
    mouseFocusWidgets.remInterface(*this);
}
