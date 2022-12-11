#ifndef THORSANVIL_WIDGETS_LAYOUT_H
#define THORSANVIL_WIDGETS_LAYOUT_H

#include "ThorsWidgetsConfig.h"
#include "Theme.h"
#include "ThorsSDL/Util.h"
#include <vector>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class Widget;
struct Theme;
class Layout
{
    bool    removeNonVisibleWidgets;
    protected:
        std::vector<UI::Sz>     layoutSize;
        std::vector<UI::Sz>     offsetPoint;

    public:
        Layout(bool removeNonVisibleWidgets = false);
        virtual ~Layout();

        UI::Sz  preferredLayout(Theme const& theme, std::vector<Widget*>& widgets);
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

enum Orientation {Horz, Vert};
enum HorzAlign {Left, Middle, Right};
enum VertAlign {Top, Center, Bottom};

inline std::ostream& operator<<(std::ostream& stream, Orientation o) {return stream << (o == Horz ? "Horz" : "Vert");}
inline std::ostream& operator<<(std::ostream& stream, HorzAlign a) {return stream << (a == Left ? "Left" : (a == Middle ? "Middle" : "Right"));}
inline std::ostream& operator<<(std::ostream& stream, VertAlign a) {return stream << (a == Top  ? "Top"  : (a == Center ? "Center" : "Bottom"));}

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

template<Orientation orientation>
class BoxLayout: public Layout
{
    static int constexpr majorAxis   = BoxLayoutTraits<orientation>::majorAxis;
    static int constexpr minorAxis   = BoxLayoutTraits<orientation>::minorAxis;

    public:
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets) override
        {
            // See Layout and WidgetView for how this is being used.
            // Step 1:  Clear the layoutSize container.
            // Step 2:  Ask each widget in the view its size and store the size in layoutSize
            // Step 3:  Call getSize()
            //              This function uses the size information that was collected
            //              to calculating the size of the bounding box and any border.
            //
            //              It also calculates the offset of each Widget from the top left
            //              of the bounding box based on alignment.
            //
            //              Note: BoxLayout is either Horizontal or Vertical.
            //                    Each visible element is placed Right or Below the previous one.
            //                    The Hight or Width is the size of the largest element.

            // Start off with a size zero.
            UI::Sz  result{0, 0};

            // Add the size of each widget (plus padding)
            for (auto const& size: layoutSize)
            {
                result[majorAxis]    += size[majorAxis] + theme.viewPadding;
                result[minorAxis]    = std::max(result[minorAxis], size[minorAxis]);
            }

            // Don't need the padding after last element.
            result[majorAxis] -= theme.viewPadding;

            // Add space for a border.
            result.x += theme.viewBorder.x + theme.viewBorder.w;
            result.y += theme.viewBorder.y + theme.viewBorder.h;
            std::cerr << "Result: " << result << "\n";

            // The location of the first widget is relative to the top left.
            // Taking into account the border.
            ThorsAnvil::UI::Sz  offset{theme.viewBorder.x, theme.viewBorder.y};
            std::cerr << "TL: " << offset << "\n";

            // Loop over the widget size information and calculate the offset of each
            // visible element based on the alignment.
            for (std::size_t index = 0; index < layoutSize.size(); ++index)
            {
                auto const& size = layoutSize[index];
                Widget& widget = *widgets[index];

                offset[minorAxis]   = alignWidget(theme, result, size, widget);

                // Store the information
                offsetPoint.emplace_back(offset);
                std::cerr << "Size:     " << size << "\n";
                std::cerr << "Location: " << offset << "\n";

                // Add offset to the major accesses for the next widget location.
                offset[majorAxis]    += size[majorAxis] + theme.viewPadding;
            }
            // Returns the size of the rectangle
            return result;
        }
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget) = 0;
};

template<Orientation orientation>
class SimpleBoxLayout: public BoxLayout<orientation>
{
    using Align = typename BoxLayoutTraits<orientation>::Align;
    static int constexpr minorAxis   = BoxLayoutTraits<orientation>::minorAxis;

    Align align;

    public:
        SimpleBoxLayout(Align align)
            : align(align)
        {}
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& /*widget*/) override
        {
            switch (align)
            {
                std::cerr << "Align: " << align << "\n";
                // Aligns either:
                //      Left / Middle / Right
                // or   Top / Center / Bottom
                case 0: std::cerr << "0\n"; return theme.viewBorder[minorAxis];
                case 1: std::cerr << "1\n"; return (fitIntoSize[minorAxis] - widgetSize[minorAxis]) / 2;
                case 2: std::cerr << "2\n"; return fitIntoSize[minorAxis] - widgetSize[minorAxis] - theme.viewBorder[minorAxis + 2];
            }
            return 0;
        }
};

using HorzBoxLayout = SimpleBoxLayout<Horz>;
using VertBoxLayout = SimpleBoxLayout<Vert>;

class GroupLayout: public BoxLayout<Vert>
{
    static int constexpr minorAxis   = BoxLayoutTraits<Vert>::minorAxis;

    public:
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget) override;
};

class GridLayout: public Layout
{
    int             xMax;
    HorzAlign       hAlign;
    VertAlign       vAlign;
    public:
        GridLayout(int width, HorzAlign hAlign, VertAlign vAlign);
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets) override;
};

}

#endif
