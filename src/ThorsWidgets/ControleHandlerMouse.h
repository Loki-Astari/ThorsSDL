#ifndef THORSANVIL_WIDGETS_CONTROLE_HANDLER_MOUSE_H
#define THORSANVIL_WIDGETS_CONTROLE_HANDLER_MOUSE_H

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include <functional>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class WidgetView;
class FocusTrackerMouse;

class ControleHandlerMouse
{
    protected:
        FocusTrackerMouse&          mouseFocusWidgets;
        std::function<UI::Rect()>   gRect;
        std::function<bool()>       iVis;
    public:
        ControleHandlerMouse(WidgetView& parentWidget, std::function<UI::Rect()>&& geRect, std::function<bool()>&& iVis);
        virtual ~ControleHandlerMouse();

                bool        isVisible() const   {return iVis();}
                UI::Rect    getRect() const     {return gRect();}

        virtual void    handleEventMouseMoveInWidget()                          {}
        virtual void    handleEventMouseMoveEnterWidget()                       {}
        virtual void    handleEventMouseMoveLeaveWidget()                       {}
        virtual void    handleEventMouseDownInWidget()                          {}
        virtual void    handleEventMouseUpInWidget()                            {}
        virtual void    handleEventMouseUpOutsideWidget()                       {}
};

}

#endif
