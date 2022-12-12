#ifndef THORSANVIL_WIDGETS_WIDGET_H
#define THORSANVIL_WIDGETS_WIDGET_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

enum WidgetType {Unknown, Label};

class Layout;
class WidgetView;
struct Theme;
class Widget
{
    WidgetView&         parent;
    UI::Pt              topLeft;
    UI::Sz              size;
    UI::TimePoint       lastUpdate;
    bool                visible;

    protected:
        UI::Pt const&  getDrawPosition()    const   {return topLeft;}
        UI::Sz const&  getDrawSize()        const   {return size;}
        UI::Rect       getBoundingRect()    const   {return {topLeft.x, topLeft.y, size.x, size.y};}

    public:
        Widget(WidgetView& parent, UI::Sz size, bool visible = true);
        virtual ~Widget();

        UI::Sz          preferredLayout(UI::DrawContext& context, Theme const& theme);
        void            performLayout(UI::Pt newTopLeft, Theme const& theme);
        virtual UI::Sz  doPreferredLayout(UI::DrawContext& /*drawContext*/, Theme const& /*theme*/, UI::Sz size)          {return size;}
        virtual void    doPerformLayout(UI::Pt /*newTopLeft*/, Theme const& /*theme*/)  {}
        virtual void    drawWidget(UI::DrawContext& drawContext, Theme const& theme)    = 0;


        virtual WidgetType  type() const        {return Unknown;}
        bool                isVisible() const   {return visible;}

        bool    handleEventMouseMoveInWidget(SDL_MouseMotionEvent const& event);
        virtual void    handleEventMouseMoveInWidgetAction(SDL_MouseMotionEvent const& event);


        virtual void    handleEventMouseMoveEnterWidget();
        virtual void    handleEventMouseMoveLeaveWidget();
};

}

#endif
