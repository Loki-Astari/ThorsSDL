#include "ControleHandlerKeyboard.h"
#include "WidgetView.h"
#include "FocusTrackerKeyboard.h"

using namespace ThorsAnvil::Widgets;


ControleHandlerKeyboard::ControleHandlerKeyboard(WidgetView& parentWidget, std::function<bool()>&& iVis)
    : keyboardFocusWidgets(parentWidget.getKeyboardInterfaceSet())
    , iVis(std::move(iVis))
{
    keyboardFocusWidgets.addInterface(*this);
}

ControleHandlerKeyboard::~ControleHandlerKeyboard()
{
    keyboardFocusWidgets.remInterface(*this);
}
