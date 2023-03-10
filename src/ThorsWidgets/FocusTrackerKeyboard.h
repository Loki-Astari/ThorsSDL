#ifndef THORSANVIL_WIDGETS_FOCUS_TRACKER_KEYBOARD_H
#define THORSANVIL_WIDGETS_FOCUS_TRACKER_KEYBOARD_H

/*
 * FocusTrackerKeyboard:
 *  Used by View to track all Widgets that can accept keyboard input.
 *  Then tracks the current widget that accepts keyboard input.
 *  forward all keyboard / text events to the widget that can handle text input
 */

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include <list>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class Widget;
class FocusTrackerMouse;
class ControleHandlerKeyboard;

class FocusTrackerKeyboard
{
    using Storage   = std::list<ControleHandlerKeyboard*>;
    using Iterator  = Storage::iterator;

    Storage     textInputWidgets;
    Iterator    current;


    public:
        FocusTrackerKeyboard();
        void reset();
        void moveKeyboardFocusToNextAvailableWidget(bool forward);

        // Adding new Widgets that can handle text.
        void addInterface(ControleHandlerKeyboard& interface);
        void remInterface(ControleHandlerKeyboard& interface);

    private:
        // TODO Move to MouseFocusSet
        friend class FocusTrackerMouse;
        void handleEventMouseDown(Widget& mouseDownIn);

    private:
        // Handle mouse and keyboard events.
        friend class View;
        void handleEventKeyDown(SDL_KeyboardEvent const& event);
        void handleEventKeyUp(SDL_KeyboardEvent const& event);
        void handleEventTextEditting(SDL_TextEditingEvent const& event);
        void handleEventTextInput(SDL_TextInputEvent const& event);
        void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event);

    private:
        // Internal Utility functions.
        Iterator findNextWidget(bool forward);
        template<typename I, typename F>
        bool searchNextKeyboardFocus(I begin, I end, F&& extract);
};

}

#endif
