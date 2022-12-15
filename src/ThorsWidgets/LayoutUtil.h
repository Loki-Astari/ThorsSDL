#ifndef THORSANVIL_WIDGETS_LAYOUT_UTIL_H
#define THORSANVIL_WIDGETS_LAYOUT_UTIL_H

#include "ThorsWidgetsConfig.h"
#include <iostream>

namespace ThorsAnvil::Widgets
{

enum Orientation {Horz, Vert};
enum HorzAlign {Left, Middle, Right};
enum VertAlign {Top, Center, Bottom};
enum GridStyle {Square, FixedHeight, FixedWidth};

// Square: =>       Same as FixedHeight and FixedWidth
// FixedHeight:     The height of each row in the grid is the same.
//                  This means we find the hight of the largest element in the grid.
//                  Each column has a fixed width, but each column may have its own width.
//                  This means we find the width of the largest element in each column.
// FixedWidth:      Inverse of FixedHeigth!
//                  The width of each column in the grid is the same.
//                  This means we find the width of the largest element in the grid.
//                  Each row has a fixed height, but each row may have its own height.
//                  This means we find the height of the largest element in each row.

inline std::ostream& operator<<(std::ostream& stream, Orientation o) {return stream << (o == Horz ? "Horz" : "Vert");}
inline std::ostream& operator<<(std::ostream& stream, HorzAlign a) {return stream << (a == Left ? "Left" : (a == Middle ? "Middle" : "Right"));}
inline std::ostream& operator<<(std::ostream& stream, VertAlign a) {return stream << (a == Top  ? "Top"  : (a == Center ? "Center" : "Bottom"));}

}

#endif
