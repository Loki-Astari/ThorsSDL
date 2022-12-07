#ifndef THORSANVIL_WIDGETS_LAYOUT_H
#define THORSANVIL_WIDGETS_LAYOUT_H

#include "ThorsWidgetsConfig.h"
#include "ThorsSDL/Util.h"
#include <vector>

namespace ThorsAnvil::Widgets
{

namespace UI = ThorsAnvil::UI;

class Widget;
class Theme;
class Layout
{
    protected:
        std::vector<UI::Sz>     layoutSize;
        std::vector<UI::Sz>     offsetPoint;
    public:
        virtual ~Layout();

        // preferredLayout
        void clear()                {layoutSize.clear();}
        void addWidget(UI::Sz size) {layoutSize.emplace_back(size);}

        // Calculates size.
        virtual UI::Sz getSize(Theme const& theme)    = 0;

        // performLayout
        UI::Sz getOffset(int index) {return offsetPoint[index];}

};

class BoxLayout: public Layout
{
    public:
        virtual UI::Sz getSize(Theme const& theme) override;
};

}

#endif
