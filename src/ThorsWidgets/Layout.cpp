#include "Layout.h"
#include "Widget.h"
#include <algorithm>

using namespace ThorsAnvil::Widgets;

Layout::Layout(bool removeNonVisibleWidgets)
    : removeNonVisibleWidgets(removeNonVisibleWidgets)
{}

Layout::~Layout()
{}

UI::Sz Layout::preferredLayout(UI::DrawContext& drawContext, Theme const& theme, std::vector<Widget*>& widgets)
{
    layoutSize.clear();

    int index = 0;
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        layoutSize.emplace_back(widget->preferredLayout(drawContext, theme));
        ++index;
    }
    return getSize(theme, widgets);
}

void Layout::performLayout(UI::Pt topLeft, Theme const& theme, std::vector<Widget*>& widgets)
{
    int index = 0;
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        UI::Sz offset = offsetPoint[index];
        widget->performLayout(topLeft + offset, theme);
        ++index;
    }
}

void Layout::drawWidget(UI::DrawContext& drawContext, Theme const& theme, std::vector<Widget*>& widgets)
{
    int index = 0;
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        widget->drawWidget(drawContext, theme);
        ++index;
    }
}

template<Orientation orientation>
UI::Sz BoxLayout<orientation>::getSize(Theme const& theme, std::vector<Widget*>& widgets)
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
    // std::cerr << "Result: " << result << "\n";

    // The location of the first widget is relative to the top left.
    // Taking into account the border.
    UI::Sz  offset{theme.viewBorder.x, theme.viewBorder.y};
    // std::cerr << "TL: " << offset << "\n";

    // Loop over the widget size information and calculate the offset of each
    // visible element based on the alignment.
    for (std::size_t index = 0; index < layoutSize.size(); ++index)
    {
        auto const& size = layoutSize[index];
        Widget& widget = *widgets[index];

        offset[minorAxis]   = alignWidget(theme, result, size, widget);

        // Store the information
        offsetPoint.emplace_back(offset);
        // std::cerr << "Size:     " << size << "\n";
        // std::cerr << "Location: " << offset << "\n";

        // Add offset to the major accesses for the next widget location.
        offset[majorAxis]    += size[majorAxis] + theme.viewPadding;
    }
    // Returns the size of the rectangle
    return result;
}

template<Orientation orientation>
SimpleBoxLayout<orientation>::SimpleBoxLayout(Align align)
    : align(align)
{}

template<Orientation orientation>
int SimpleBoxLayout<orientation>::alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& /*widget*/)
{
    switch (align)
    {
        // std::cerr << "Align: " << align << "\n";
        // Aligns either:
        //      Left / Middle / Right
        // or   Top / Center / Bottom
        case 0: return theme.viewBorder[minorAxis];
        case 1: return (fitIntoSize[minorAxis] - widgetSize[minorAxis]) / 2;
        case 2: return fitIntoSize[minorAxis] - widgetSize[minorAxis] - theme.viewBorder[minorAxis + 2];
    }
    return 0;
}

int GroupLayout::alignWidget(Theme const& theme, UI::Sz fitIntoSize, UI::Sz widgetSize, Widget const& widget)
{
    // Labels aligned on the Left:
    if (widget.type() == Label) {
        return theme.viewBorder[minorAxis];
    }
    // Everything else Right Aligned.
    return fitIntoSize[minorAxis] - widgetSize[minorAxis] - theme.viewBorder[minorAxis + 2];
}

GridLayout::GridLayout(int width, HorzAlign hAlign, VertAlign vAlign)
    : xMax(width)
    , hAlign(hAlign)
    , vAlign(vAlign)
{}

UI::Sz GridLayout::getSize(Theme const& theme, std::vector<Widget*>& /*widgets*/)
{
    UI::Sz  mazElementSize{0, 0};

    // Step 1:  Calculate the dimensions of each Grid box.
    //          This will take the largest X size of widgets and the largest Y size.
    //          In the grid each cell will be the same size.
    int yMax = 0;
    for (int y = 0; yMax == 0; ++y)
    {
        for (int x = 0; x < xMax; ++x)
        {
            std::size_t index = y * xMax + x;
            if (index >= layoutSize.size())
            {
                yMax = y + 1;
                break;
            }

            mazElementSize.x    = std::max(mazElementSize.x, layoutSize[index].x);
            mazElementSize.y    = std::max(mazElementSize.y, layoutSize[index].y);
        }
    }

    // Step 2:  Calculate the size of the View.
    //          Border / Padding / size of cell taken into account.
    int xSize   = (theme.viewBorder.x + theme.viewBorder.w) + (xMax *  (mazElementSize.x + theme.viewPadding)) - (xMax == 0 ? 0 : theme.viewPadding);
    int ySize   = (theme.viewBorder.y + theme.viewBorder.h) + (yMax *  (mazElementSize.y + theme.viewPadding)) - (yMax == 0 ? 0 : theme.viewPadding);

    UI::Sz  result{xSize, ySize};

    // Step 3:  Calculate the offset from the top left of each widget
    //          Take into account alignment.
    yMax = 0;
    for (int y = 0; yMax == 0; ++y)
    {
        for (int x = 0; x < xMax; ++x)
        {
            std::size_t index = y * xMax + x;
            if (index >= layoutSize.size())
            {
                yMax = y + 1;
                break;
            }

            int xOffset;
            int yOffset;
            switch (hAlign)
            {
                case 0: xOffset = 0; break;
                case 1: xOffset = (mazElementSize.x - layoutSize[index].x) / 2; break;
                case 2: xOffset = mazElementSize.x - layoutSize[index].x;
            }
            switch (vAlign)
            {
                case 0: yOffset = 0; break;
                case 1: yOffset = (mazElementSize.y - layoutSize[index].y) / 2; break;
                case 2: yOffset = mazElementSize.y - layoutSize[index].y;
            }

            // Position from top left is border + cell size + padding size + alignment offset.
            int xPos = theme.viewBorder.x + (x * (mazElementSize.x + theme.viewPadding)) + xOffset;
            int yPos = theme.viewBorder.y + (y * (mazElementSize.y + theme.viewPadding)) + yOffset;

            offsetPoint.emplace_back(UI::Sz{xPos, yPos});
        }
    }

    // Return the size of the view.
    // Calculated in Step 2
    return result;
}

namespace ThorsAnvil::Widgets
{
    template class BoxLayout<Horz>;
    template class BoxLayout<Vert>;

    template class SimpleBoxLayout<Horz>;
    template class SimpleBoxLayout<Vert>;
}
