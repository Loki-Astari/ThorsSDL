#ifndef THORSANVIL_WIDGETS_EVENT_FOCUS_MOUSE_H
#define THORSANVIL_WIDGETS_EVENT_FOCUS_MOUSE_H

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include <list>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class WidgetMouseFocusInterface;
class EventFocusKeyboard;

class EventFocusMouse
{
    using Storage   = std::list<WidgetMouseFocusInterface*>;
    using Iterator  = Storage::iterator;

    Storage     mouseInputWidgets;
    Iterator    mouseOver;
    Iterator    mouseDownIn;


    Iterator    none()                  {return std::end(mouseInputWidgets);}
    bool        isValid(Iterator iter)  {return iter != std::end(mouseInputWidgets);}

    public:
        EventFocusMouse();
        // Adding new Widgets that can handle text.
        void addInterface(WidgetMouseFocusInterface& interface);
        void remInterface(WidgetMouseFocusInterface& interface);
        void handleEventMouseMoveEnterWidget(SDL_WindowEvent const& /*event*/);
        void handleEventMouseMoveLeaveWidget(SDL_WindowEvent const& /*event*/);
        void handleEventMouseMoveInWidget(UI::Pt const& mousePosition);
        void handleEventMouseDownInWidget(SDL_MouseButtonEvent const& /*event*/, EventFocusKeyboard& /*textInputSet*/);
        void handleEventMouseUpInWidget(SDL_MouseButtonEvent const& /*event*/);
};

}

#endif
