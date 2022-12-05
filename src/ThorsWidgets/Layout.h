#ifndef THORSANVIL_WIDGETS_LAYOUT_H
#define THORSANVIL_WIDGETS_LAYOUT_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class Widget;
class Layout
{
    public:
        virtual ~Layout();

        virtual UI::Pt  preferredLayout(Widget& widget) const = 0;
        virtual void    performLayout(Widget& widget)   const = 0;
};

class BoxLayout: public Layout
{
    public:
        virtual UI::Pt  preferredLayout(Widget& widget) const;
        virtual void    performLayout(Widget& widget)   const;
};

}

#endif
