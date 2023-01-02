#ifndef THORSANVIL_WIDGETS_TEXT_INPUT_INTERFACE_H
#define THORSANVIL_WIDGETS_TEXT_INPUT_INTERFACE_H

/*
 * KeyboardFocusSet:
 *  Used by View to track all Widgets that can accept keyboard input.
 *  Then tracks the current widget that accepts keyboard input.
 *  forward all keyboard / text events to the widget that can handle text input
 */

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include <list>

namespace ThorsAnvil::Widgets
{

class Widget;

class KeyboardFocusSet
{
    using Storage   = std::list<WidgetKeyboardFocusInterface*>;
    using Iterator  = Storage::iterator;

    Storage     textInputWidgets;
    Iterator    current;


    public:
        KeyboardFocusSet();
        void reset();
        void moveKeyboardFocusToNextAvailableWidget(bool forward);

    private:
        // Adding new Widgets that can handle text.
        friend class WidgetKeyboardFocusInterface;
        void addInterface(WidgetKeyboardFocusInterface& interface);
        void remInterface(WidgetKeyboardFocusInterface& interface);

    private:
        // Handle mouse and keyboard events.
        friend class View;
        void handleEventMouseDown(Widget& mouseDownIn);
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
