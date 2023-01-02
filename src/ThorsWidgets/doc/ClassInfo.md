Dialog.h
    Class Dialog:
        Creates a dialog from a set of types and a set of labels.
            Types:  Template
            Labels: Construtctor
        The Dialog has an "OK" button that calls a callback with all the data when pressed then hides the dialog.

Layout.h
    Virtual Class Layout:
        Base class for layout.
    Classes: HorzBoxLayout/ VertBoxLayout/ GridLayout


    In Layout we have all the code that does the layout.
    The sub-classes implement getSize() to get size information about the widgets and define layoutSize/offsetPoint

        virtual UI::Sz getSize(Theme const& theme, std::vector<Widget*>& widgets)    = 0;

            This is called by preferredLayout() after we have retrieved the size of all "visible" children.
            The size of each child is stored in "layoutSize".

            This function should use this size information to calculate the size of the bounding box to hold
            all the children (and return this value) and store the offset of each "visible" child within the
            bounding box (in "offsetPoint").

    HorzBoxLayout:     Aligns cells in 1D grid.
            Bounding Box:  X: The sum of the length of the widgets.
                           Y: The height of the largest widget.
                              Each cell is the correct size horizontally, but may be two large vertically.
                              Each widget will be aligned (as per constructor argument vertically within the cell.
    VertBoxLayout:     The same as HorzBoxLayout (but in vertical direction (so swap X/Y statements above)
    GridLayout:        Aligns cells in 2D grid.
                           The width (in cells) is fixed and defined by constructor. The height (in cells) depends on
                           the number of widgets being laid out.
                           Three Styles:
                                Square:     We treat the grid as a set of Rectangles.
                                            X/Y size determined by the size of the max X/Y size
                                            of all the widgets.
                                FixedHeight:All rows have the same height. Each column has a fixed but independent width.
                                FixedWidth: All columns have the same width. Each row has a fixed but independent height.
                            Alignment inside each cell is defined by the constructor and the space available.


Theme.h
    Class Theme
        Defines how to draw all standard elements.
        Should be able to redefine basic parameters of all widgets in this one class.

View.h
    The override of ThorsUI/view.h that handles drawing a view of Widgets.

    class View

Widget.h
    The basic drawable object.
    Virtual class Widget

WidgetView.h
    A Widget that holds other Widgets.
    Uses a layout to decide how all the child widgets are laid out.

WidgetLabel.h
    A Label (simply displays some text)

WidgetButton.h
    A Button (with Text) that can be pressed.
    WidgetButton

WidgetInputText.h
    A text input class.
        WidgetInputText

KeyboardFocusSet.h
    An object used by View to track Widgets than can handle keyboard / text events.
