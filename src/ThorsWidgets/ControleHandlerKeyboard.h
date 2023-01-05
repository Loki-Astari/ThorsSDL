#ifndef THORSANVIL_WIDGETS_CONTROLE_HANDLER_KEYBOARD_H
#define THORSANVIL_WIDGETS_CONTROLE_HANDLER_KEYBOARD_H

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include <functional>
#include <string_view>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class WidgetView;
class FocusTrackerKeyboard;

/*
 * A Widget that accepts Keyboard Focus
 */
class ControleHandlerKeyboard
{
    protected:
        FocusTrackerKeyboard&       keyboardFocusWidgets;
        std::function<bool()>       iVis;
    public:
        ControleHandlerKeyboard(WidgetView& parentWidget, std::function<bool()>&& iVis);
        virtual ~ControleHandlerKeyboard();

                bool    isVisible() const   {return iVis();}

        virtual void    handleEventTextGainFocus()                                      {}
        virtual void    handleEventTextLoseFocus()                                      {}
        virtual void    handleEventTextInsert(Uint16 /*keyMod*/, SDL_Keycode /*key*/)   {}
        virtual void    handleEventTextInsert(std::string_view /*view*/)                {}
};

}

#endif
