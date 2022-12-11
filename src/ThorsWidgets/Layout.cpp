#include "Layout.h"
#include "Widget.h"
#include <algorithm>

using namespace ThorsAnvil::Widgets;

Layout::Layout(bool removeNonVisibleWidgets)
    : removeNonVisibleWidgets(removeNonVisibleWidgets)
{}

Layout::~Layout()
{}

ThorsAnvil::UI::Sz Layout::preferredLayout(Theme const& theme, std::vector<Widget*>& widgets)
{
    layoutSize.clear();

    int index = 0;
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        layoutSize.emplace_back(widget->preferredLayout(theme));
        ++index;
    }
    return getSize(theme, widgets);
}

void Layout::performLayout(ThorsAnvil::UI::Pt topLeft, Theme const& theme, std::vector<Widget*>& widgets)
{
    int index = 0;
    for (auto widget: widgets)
    {
        if (removeNonVisibleWidgets && !widget->isVisible()) {
            continue;
        }
        ThorsAnvil::UI::Sz offset = offsetPoint[index];
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

ThorsAnvil::UI::Sz GridLayout::getSize(Theme const& theme, std::vector<Widget*>& /*widgets*/)
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

            offsetPoint.emplace_back(ThorsAnvil::UI::Sz{xPos, yPos});
        }
    }

    // Return the size of the view.
    // Calculated in Step 2
    return result;
}
