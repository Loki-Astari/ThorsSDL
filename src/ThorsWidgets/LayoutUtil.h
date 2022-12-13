#ifndef THORSANVIL_WIDGETS_LAYOUT_UTIL_H
#define THORSANVIL_WIDGETS_LAYOUT_UTIL_H

#include "ThorsWidgetsConfig.h"
#include <iostream>

namespace ThorsAnvil::Widgets
{

enum Orientation {Horz, Vert};
enum HorzAlign {Left, Middle, Right};
enum VertAlign {Top, Center, Bottom};

inline std::ostream& operator<<(std::ostream& stream, Orientation o) {return stream << (o == Horz ? "Horz" : "Vert");}
inline std::ostream& operator<<(std::ostream& stream, HorzAlign a) {return stream << (a == Left ? "Left" : (a == Middle ? "Middle" : "Right"));}
inline std::ostream& operator<<(std::ostream& stream, VertAlign a) {return stream << (a == Top  ? "Top"  : (a == Center ? "Center" : "Bottom"));}

}

#endif
