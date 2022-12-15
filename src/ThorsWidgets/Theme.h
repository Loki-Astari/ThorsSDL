#ifndef THORSANVIL_WIDGETS_THEME_H
#define THORSANVIL_WIDGETS_THEME_H

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include "ThorsUI/DrawContext.h"
#include "ThorsUI/Pen.h"

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class WidgetView;
class WidgetLabel;
class WidgetButton;

class ThemeUtility
{
    public:
        static UI::TextPen getPen(std::string const& font, int point, UI::Color color)
        {
            static const std::string fontPath = "/System/Library/Fonts/Supplemental/";
            return UI::TextPen(fontPath + font + ".ttf", point, color);
        }
};

struct Theme
{
    // Brush Script
    UI::TextPen normalTextPen   = ThemeUtility::getPen("Arial", 16, UI::C::lightgrey);
    UI::TextPen hoverTextPen    = ThemeUtility::getPen("Arial", 16, UI::C::darkslateblue);
    UI::TextPen pressTextPen    = ThemeUtility::getPen("Arial", 16, UI::C::white);

    UI::Pen     buttonBorderPen = UI::Pen(UI::C::white, UI::C::antiquewhite);
    UI::Pen     buttonPressedPen= UI::Pen(UI::C::white, UI::C::black);

    int         windowPadding   = 2;
    int         viewPadding     = 2;            // Space between elements in a view
    UI::Rect    viewBorder      = {2, 2, 2, 2}; // Space around all elements to display border; Left, Top, Right, Bottom
    UI::Rect    labelBorder     = {2, 2, 2, 2};
    int         buttonLineWidth = 2;
    UI::Rect    buttonBorder    = {2, 2, 2, 2};
    UI::Rect    buttonPadding   = {2, 2, 2, 2};

    virtual void drawWidget(UI::DrawContext&, WidgetView const&) const;
    virtual void drawWidget(UI::DrawContext&, WidgetLabel const&) const;
    virtual void drawWidget(UI::DrawContext&, WidgetButton const&) const;

};

}

#endif
