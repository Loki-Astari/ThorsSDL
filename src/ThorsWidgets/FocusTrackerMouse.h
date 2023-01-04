#ifndef THORSANVIL_WIDGETS_EVENT_FOCUS_MOUSE_H
#define THORSANVIL_WIDGETS_EVENT_FOCUS_MOUSE_H

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include <list>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class WidgetMouseFocusInterface;
class FocusTrackerKeyboard;

class FocusTrackerMouse
{
    using Storage   = std::list<WidgetMouseFocusInterface*>;
    using Iterator  = Storage::const_iterator;

    Storage     mouseInputWidgets;
    Iterator    mouseOver;
    Iterator    mouseDownIn;
    Iterator    widgetPressed;


    Iterator    none()                  const {return std::cend(mouseInputWidgets);}
    bool        isValid(Iterator iter)  const {return iter != std::cend(mouseInputWidgets);}

    public:
        FocusTrackerMouse();
        // Adding new Widgets that can handle text.
        void addInterface(WidgetMouseFocusInterface& interface);
        void remInterface(WidgetMouseFocusInterface& interface);
        WidgetMouseFocusInterface*  getWidgetPressed()    const {return widgetPressed == none() ? nullptr : *widgetPressed;}

    private:
        friend class View;
        void handleEventMouseMoveEnterWidget(SDL_WindowEvent const& event);
        void handleEventMouseMoveLeaveWidget(SDL_WindowEvent const& event);
        void handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event);
        void handleEventMouseDownInWidget(SDL_MouseButtonEvent const& event);
        void handleEventMouseUpInWidget(SDL_MouseButtonEvent const& event);
};

}

#endif
