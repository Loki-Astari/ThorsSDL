#include "ControleHandlerMouse.h"
#include "WidgetView.h"
#include "FocusTrackerMouse.h"

using namespace ThorsAnvil::Widgets;


ControleHandlerMouse::ControleHandlerMouse(WidgetView& parentWidget, std::function<UI::Rect()>&& gRect, std::function<bool()>&& iVis)
    : mouseFocusWidgets(parentWidget.getMouseInterfaceSet())
    , gRect(std::move(gRect))
    , iVis(std::move(iVis))
{
    mouseFocusWidgets.addInterface(*this);
}

ControleHandlerMouse::~ControleHandlerMouse()
{
    mouseFocusWidgets.remInterface(*this);
}
