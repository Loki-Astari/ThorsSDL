#ifndef THORSANVIL_WIDGETS_THEME_H
#define THORSANVIL_WIDGETS_THEME_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"
#include "ThorsSDL/DrawContext.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class WidgetView;
class WidgetLabel;
struct Theme
{
    int         viewPadding     = 2;            // Space between elements in a view
    UI::Rect    viewBorder      = {2, 2, 2, 2}; // Space around all elements to display border; Left, Top, Right, Bottom
    UI::Rect    labelBorder     = {2, 2, 2, 2};

    virtual void drawWidget(UI::DrawContext&, WidgetView const&) const;
    virtual void drawWidget(UI::DrawContext&, WidgetLabel const&) const;
};

}

#endif
