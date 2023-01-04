#ifndef THORSANVIL_WIDGETS_LAYOUT_H
#define THORSANVIL_WIDGETS_LAYOUT_H

#include "ThorsWidgetsConfig.h"
#include "LayoutUtil.h"
#include "ThorsUI/DrawContext.h"
#include "ThorsUI/Util.h"
#include <vector>

/*
 * Layout types:
 *      HorzBoxLayout:     Aligns cells in 1D grid.
 *          Bounding Box:  X: The sum of the length of the widgets.
 *                         Y: The height of the largest widget.
 *                            Each cell is the correct size horizontally, but may be two large vertically.
 *                            Each widget will be aligned (as per constructor argument vertically within the cell.
 *      VertBoxLayout:     The same as HorzBoxLayout (but in vertical direction (so swap X/Y statements above)
 *      GridLayout:        Aligns cells in 2D grid.
 *                         The width (in cells) is fixed and defined by constructor. The height (in cells) depends on
 *                         the number of widgets being laid out.
 *                         Three Styles:
 *                              Square:     We treat the grid as a set of Rectangles.
 *                                          X/Y size determined by the size of the max X/Y size
 *                                          of all the widgets.
 *                              FixedHeight:All rows have the same height. Each column has a fixed but independent width.
 *                              FixedWidth: All columns have the same width. Each row has a fixed but independent height.
 *                          Alignment inside each cell is defined by the constructor and the space available.
 *
 * Usage:
 *      HorzBoxLayout       horizontal(Bottom);                     // Each widget laid out horizontally. Aligned to the bottom of the cell (that is exactly wide enough).
 *      VertBoxLayout       horizontal(Left);                       // Each Widget laid out vertically. Aligned to the left of the cell (that is exactly high enough).
 *      GridLayout          grid(4, Square, Center, Middle);        // A 4 by N grid of widgets. Each cell has the same height and width. The widgets are placed in the center of the cell.
 */

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;
class Widget;
struct Theme;

namespace Util
{
    /*
     * Utility Class used by SimpleBoxLauput
     * This is used to allow Horizontal and Vertical Layouts to be defined using a single class.
     */
    template<Orientation>
    struct BoxLayoutTraits;

    template<>
    struct BoxLayoutTraits<Horz>
    {
        using Align = HorzAlign;
        static int constexpr majorAxis = 0;
        static int constexpr minorAxis = 1;
    };
    template<>
    struct BoxLayoutTraits<Vert>
    {
        using Align = VertAlign;
        static int constexpr majorAxis = 1;
        static int constexpr minorAxis = 0;
    };

}
// The base layout from which all other layouts are derived.
class Layout
{
    bool    removeNonVisibleWidgets;
    protected:
        std::vector<UI::Sz>     layoutSize;
        std::vector<UI::Sz>     offsetPoint;

    public:
        Layout(bool removeNonVisibleWidgets = false);
        virtual ~Layout();

        UI::Sz  preferredLayout(UI::DrawContext& drawContext, Theme const& theme, std::vector<Widget*>& widgets);
        void    performLayout(UI::Pt topLeft, Theme const& theme, std::vector<Widget*>& widgets);
        void    drawWidget(UI::DrawContext& drawContext, Theme const& theme, std::vector<Widget*>& widgets);

    private:
        // This is called by preferredLayout() after we have retrieved the size of all "visible" children.
        // This function should use this size information to calculate the size of the bounding box to hold
        // all the children and store the offset of each "visible" child within the bounding box.
        // Note: performLayout() will call performLayout() on each child passing it the absolute top left of
        //       its position so that it knows where it will be drawn.
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets)    = 0;
};

template<Orientation orientation>
class BoxLayout: public Layout
{
    static int constexpr majorAxis   = Util::BoxLayoutTraits<orientation>::majorAxis;
    static int constexpr minorAxis   = Util::BoxLayoutTraits<orientation>::minorAxis;

    public:
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets) override;
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget) = 0;
};

template<Orientation orientation>
class SimpleBoxLayout: public BoxLayout<orientation>
{
    using Align = typename Util::BoxLayoutTraits<orientation>::Align;
    static int constexpr minorAxis   = Util::BoxLayoutTraits<orientation>::minorAxis;

    Align align;

    public:
        SimpleBoxLayout(Align align);
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& /*widget*/) override;
};

using HorzBoxLayout = SimpleBoxLayout<Horz>;
using VertBoxLayout = SimpleBoxLayout<Vert>;

class GroupLayout: public BoxLayout<Vert>
{
    static int constexpr minorAxis   = Util::BoxLayoutTraits<Vert>::minorAxis;

    public:
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget) override;
};

class GridLayout: public Layout
{
    int             xMax;
    GridStyle       style;
    HorzAlign       hAlign;
    VertAlign       vAlign;
    public:
        GridLayout(int width, GridStyle style, HorzAlign hAlign, VertAlign vAlign);
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets) override;
};

}

#endif
