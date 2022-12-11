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
        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets) override;
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget) = 0;
};

template<Orientation orientation>
class SimpleBoxLayout: public BoxLayout<orientation>
{
    using Align = typename BoxLayoutTraits<orientation>::Align;
    static int constexpr minorAxis   = BoxLayoutTraits<orientation>::minorAxis;

    Align align;

    public:
        SimpleBoxLayout(Align align);
        virtual int alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& /*widget*/) override;
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
