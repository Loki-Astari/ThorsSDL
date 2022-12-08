#include "Layout.h"
#include "Widget.h"
#include <algorithm>

using namespace ThorsAnvil::Widgets;


Layout::~Layout()
{}

ThorsAnvil::UI::Sz BoxLayout::getSize(Theme const& /*theme*/)
{
    ThorsAnvil::UI::Sz  result{0, 0};
    for (auto const& size: layoutSize)
    {
        result.x    = std::max(result.x, size.x);
        result.y    += size.y + 2;
    }

    result.y -= 2; // Don't need the offset after last element.

    ThorsAnvil::UI::Sz  offset{0,0};

    // Horizontally center each widget
    for (auto const& size: layoutSize)
    {
        offset.x    = (result.x - size.x) / 2;
        offsetPoint.emplace_back(offset);

        offset.y    += size.y + 2;
    }
    return result;
}
