#include "Layout.h"
#include "Widget.h"
#include <algorithm>
#include <numeric>

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

    // The location of the first widget is relative to the top left.
    // Taking into account the border.
    UI::Sz  offset{theme.viewBorder.x, theme.viewBorder.y};

    // Loop over the widget size information and calculate the offset of each
    // visible element based on the alignment.
    for (std::size_t index = 0; index < layoutSize.size(); ++index)
    {
        auto const& size = layoutSize[index];
        Widget& widget = *widgets[index];

        offset[minorAxis]   = alignWidget(theme, result, size, widget);

        // Store the information
        offsetPoint.emplace_back(offset);

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

GridLayout::GridLayout(int width, GridStyle style, HorzAlign hAlign, VertAlign vAlign)
    : xMax(width)
    , style(style)
    , hAlign(hAlign)
    , vAlign(vAlign)
{}

UI::Sz GridLayout::getSize(Theme const& theme, std::vector<Widget*>& /*widgets*/)
{
    UI::Sz  mazElementSize{0, 0};

    // Step 1:  Calculate the dimensions of each Grid box.
    //          This will take the largest X size of widgets and the largest Y size.
    //          In the grid each cell will be the same size.
    int yMax = layoutSize.size() / xMax + (layoutSize.size() % xMax == 0 ? 0 : 1);

    std::vector<int>        maxColWidth(xMax + 1, 0);
    std::vector<int>        maxRowHeight(yMax + 1, 0);
    for (int y = 0; y < yMax; ++y)
    {
        for (int x = 0; x < xMax; ++x)
        {
            std::size_t index = y * xMax + x;

            mazElementSize.x    = std::max(mazElementSize.x, layoutSize[index].x);
            mazElementSize.y    = std::max(mazElementSize.y, layoutSize[index].y);

            maxColWidth[x]  = std::max(maxColWidth[x], layoutSize[index].x);
            maxRowHeight[y] = std::max(maxRowHeight[y], layoutSize[index].y);
        }
    }

    // Step 2:  Calculate the size of the View.
    //          Border / Padding / size of cell taken into account.
    int xSize = (theme.viewBorder.x + theme.viewBorder.w);
    int ySize = (theme.viewBorder.y + theme.viewBorder.h);
    switch (style)
    {
        case Square:
            xSize   += xMax == 0 ? 0 : (xMax *  (mazElementSize.x + theme.viewPadding)) - theme.viewPadding;
            ySize   += yMax == 0 ? 0 : (yMax *  (mazElementSize.y + theme.viewPadding)) - theme.viewPadding;
            break;
        case FixedHeight:
            xSize   += xMax == 0 ? 0 : std::accumulate(std::begin(maxColWidth), std::end(maxColWidth), 0) + ((xMax - 1) * theme.viewPadding);
            ySize   += yMax == 0 ? 0 : (yMax *  (mazElementSize.y + theme.viewPadding)) - theme.viewPadding;
            break;
        case FixedWidth:
            xSize   += xMax == 0 ? 0 : (xMax *  (mazElementSize.x + theme.viewPadding)) - theme.viewPadding;
            ySize   += yMax == 0 ? 0 : std::accumulate(std::begin(maxRowHeight), std::end(maxRowHeight), 0) + ((yMax - 1) * theme.viewPadding);
            break;
    }

    UI::Sz  result{xSize, ySize};

    // Step 3A:  Pre compute col and row offset
    //           using the maxColWidth / maxRowHeight
    int cumlativeWidth = theme.viewBorder.x;
    for (auto& width: maxColWidth)
    {
        int thisWidth;
        switch (style)
        {
            case Square:
            case FixedWidth:
                thisWidth   = mazElementSize.x;
                break;
            case FixedHeight:
                thisWidth   = width;
                break;
        }
        width           = cumlativeWidth;
        cumlativeWidth += (thisWidth + theme.viewPadding);
    }
    maxColWidth.back() -= maxColWidth.size() == 1 ? 0 : theme.viewPadding;
    maxColWidth.back() += theme.viewBorder.w;

    int cumlativeHeight = theme.viewBorder.y;
    for (auto& height: maxRowHeight)
    {
        int thisHeight;
        switch (style)
        {
            case Square:
            case FixedHeight:
                thisHeight = mazElementSize.y;
                break;
            case FixedWidth:
                thisHeight = height;
        }
        height          = cumlativeHeight;
        cumlativeHeight+= (thisHeight + theme.viewPadding);
    }
    maxRowHeight.back() -= maxRowHeight.size() == 1 ? 0 : theme.viewPadding;
    maxRowHeight.back() += theme.viewBorder.h;

    // Step 3B:  Calculate the offset from the top left of each widget
    //          Take into account alignment.
    for (int y = 0; y < yMax; ++y)
    {
        for (int x = 0; x < xMax; ++x)
        {
            std::size_t index = y * xMax + x;

            int xPos;
            int yPos;
            switch (hAlign)
            {
                case 0: xPos = maxColWidth[x]; break;
                case 1: xPos = maxColWidth[x] + (maxColWidth[x+1] - maxColWidth[x] - theme.viewPadding - layoutSize[index].x) / 2; break;
                case 2: xPos = maxColWidth[x+1] - theme.viewPadding - layoutSize[index].x;break;
            }
            switch (vAlign)
            {
                case 0: yPos = maxRowHeight[y]; break;
                case 1: yPos = maxRowHeight[y] + (maxRowHeight[y+1] - maxRowHeight[y] - theme.viewPadding - layoutSize[index].y) / 2; break;
                case 2: yPos = maxRowHeight[y+1] - theme.viewPadding - layoutSize[index].y; break;
            }

            offsetPoint.emplace_back(UI::Sz{xPos, yPos});
        }
    }

    if ((result.x != maxColWidth.back()) || (result.y != maxRowHeight.back()))
    {
        throw std::runtime_error("Validation Check of view size did not work");
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
