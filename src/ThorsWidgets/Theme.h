#ifndef THORSANVIL_WIDGETS_THEME_H
#define THORSANVIL_WIDGETS_THEME_H

/*
 * Class Theme:
 *      Contains all the drawing code for all widgets.
 *      Thus allows a single place to override the default drawing behavior of all widgets.
 *      Thus I will implement a very redamentry theme that works.
 *      I hope somebody with skill in graphics comes along and implements something slightly more
 *      pleasant that people will actually want to use. But they will simply need to define the
 *      properties in this one class.
 */

#include "ThorsWidgetsConfig.h"
#include "ThorsUI/Util.h"
#include "ThorsUI/Pen.h"
#include <string>

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class WidgetView;
class WidgetLabel;
class WidgetInputText;
class WidgetButton;

/*
 * For now this is in the Widget Class.
 * I expect long term to move this into ThorsUI (maybe) still working on it.
 * The basic font takes an absolute path. This utility abstract the need for an absolute path.
 */
class ThemeUtility
{
    public:
        static UI::TextPen getPen(std::string const& font, int point, UI::Color ink , UI::Color background = {0, 0, 0, 255})
        {
            static const std::string fontPath[] = {   "/Library/Fonts"
                                                    , "/System/Library/Fonts/Supplemental/"
                                                    , "/System Folder/Fonts"
                                                  };
            // TODO
            // If a font is already loaded then reuse the data.
            return UI::TextPen(fontPath[1] + font + ".ttf", point, ink, background);
        }
};

struct Theme
{
    // Space around edge of View.
    int         windowPadding       = 2;

    // Space around elements in WidgetView
    int         viewPadding         = 2;            // Space between elements in a view
    UI::Rect    viewBorder          = {2, 2, 2, 2}; // Space around all elements to display border; Left, Top, Right, Bottom
    virtual void drawWidget(UI::DrawContext&, WidgetView const&) const;

    // WidgetLabels
    UI::Rect    labelBorder         = {2, 2, 2, 2};
    UI::TextPen labelNormalTextPen  = ThemeUtility::getPen("Arial Unicode", 16, UI::C::lightgrey);
    virtual void drawWidget(UI::DrawContext&, WidgetLabel const&) const;

    // WidgetInputText
    UI::Rect    inputTextBorder     = {4, 4, 4, 4};
    UI::TextPen inputNormalTextPen  = ThemeUtility::getPen("Arial Unicode", 16, UI::C::darkgrey);
    UI::Pen     inputSelectedTextPen= ThemeUtility::getPen("Arial Unicode", 16, UI::C::yellow, UI::C::yellow);
    UI::Pen     inputNormalBorderPen= UI::Pen(UI::C::white);
    UI::Pen     inputFocusBorderPen = UI::Pen(UI::C::white);
    virtual void drawWidget(UI::DrawContext&, WidgetInputText const&) const;

    // WidgetButtons
    int         buttonLineWidth     = 2;
    UI::Rect    buttonBorder        = {2, 2, 2, 2};
    UI::Rect    buttonPadding       = {2, 2, 2, 2};
    UI::TextPen butNormalTextPen    = ThemeUtility::getPen("Arial Unicode", 16, UI::C::lightgrey);
    UI::TextPen butHoverTextPen     = ThemeUtility::getPen("Arial Unicode", 16, UI::C::darkslateblue);
    UI::TextPen butPressTextPen     = ThemeUtility::getPen("Arial Unicode", 16, UI::C::white);
    UI::Pen     buttonBorderPen     = UI::Pen(UI::C::white, UI::C::antiquewhite);
    UI::Pen     buttonPressedPen    = UI::Pen(UI::C::white, UI::C::black);
    virtual void drawWidget(UI::DrawContext&, WidgetButton const&) const;
};

}

#endif
