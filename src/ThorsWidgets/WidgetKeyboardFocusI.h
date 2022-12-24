#ifndef THORSANVIL_WIDGETS_TEXT_INPUT_INTERFACE_H
#define THORSANVIL_WIDGETS_TEXT_INPUT_INTERFACE_H

#include "ThorsWidgetsConfig.h"
#include "Widget.h"
#include <list>

namespace ThorsAnvil::Widgets
{

class Widget;
class KeyboardFocusSet;
class WidgetKeyboardFocusInterface: public Widget
{
    protected:
        KeyboardFocusSet&   keyboardFocusWidgets;
    public:
        WidgetKeyboardFocusInterface(WidgetView& parentWidget, UI::Sz minSize, bool visible = true);

        virtual ~WidgetKeyboardFocusInterface();

        virtual void    acceptKeyboardFocus() = 0;
        virtual void    looseKeyboardFocus()  = 0;
};

class KeyboardFocusSet
{
    using Storage   = std::list<WidgetKeyboardFocusInterface*>;
    using Iterator  = Storage::iterator;

    Storage     textInputWidgets;
    Iterator    current;


    public:
        KeyboardFocusSet();

        void addInterface(WidgetKeyboardFocusInterface& interface);
        void remInterface(WidgetKeyboardFocusInterface& interface);
        void moveKeyboardFocusToNextAvailableWidget(bool forward);
        void reset();

        void handleEventMouseDown(Widget& mouseDownIn);
        void handleEventKeyUp(SDL_KeyboardEvent const& event);
        void handleEventTextEditting(SDL_TextEditingEvent const& event);
        void handleEventTextInput(SDL_TextInputEvent const& event);
        void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event);

    private:
        Iterator findNextWidget(bool forward);
        template<typename I, typename F>
        bool searchNextKeyboardFocus(I begin, I end, F&& extract);
};

}

#endif
