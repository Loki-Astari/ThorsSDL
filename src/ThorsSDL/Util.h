#ifndef THORSANVIL_UI_UTIL_H
#define THORSANVIL_UI_UTIL_H

#include "ThorsSDLConfig.h"
#include <SDL.h>
#include <iostream>

namespace ThorsAnvil::UI
{

static constexpr int windowUndefinedPos = SDL_WINDOWPOS_UNDEFINED;
static constexpr int windowCentered     = SDL_WINDOWPOS_CENTERED;

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

struct Pt: SDL_Point
{
    friend std::ostream& operator<<(std::ostream& s, ThorsAnvil::UI::Pt const& point)
    {
        return s << "Pt: {" << point.x << ", " << point.y << "}";
    }
};

struct Sz: SDL_Point
{
    friend std::ostream& operator<<(std::ostream& s, ThorsAnvil::UI::Sz const& point)
    {
        return s << "Sz: {" << point.x << ", " << point.y << "}";
    }
};

inline Sz operator-(Pt const& lhs, Pt const& rhs)
{
    return {rhs.x - lhs.x, rhs.y - lhs.y};
}
inline Pt& operator+=(Pt& lhs, Sz const& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}
inline Pt operator+(Pt lhs, Sz const& rhs)
{
    return lhs += rhs;
}

enum CollisionPoint {Miss, TopLeft, Top, TopRight, Right, BotRight, Bot, BotLeft, Left};

struct Rect: SDL_Rect
{
    bool contains(Pt const& pt)         const   { return (pt.x >= x && pt.x < (x + w) && pt.y >= y && pt.y < (y + h));}
    bool xIntersect(Rect const& rect)   const   { return (rect.x < x && (rect.x + rect.w) >= x) || (rect.x >= x && rect.x < (x + w));}
    bool yIntersect(Rect const& rect)   const   { return (rect.y < y && (rect.y + rect.h) >= y) || (rect.y >= y && rect.y < (y + h));}
    bool intersect(Rect const& rect)    const   { return xIntersect(rect) && yIntersect(rect);}

    CollisionPoint collision(Pt const& point, Pt const& vel) const
    {
        int     leftIntersect   = point.y + ((x - point.x + 1) * vel.y / std::abs(vel.x));
        bool    hitLeft         = (point.x < x && (point.x + vel.x) >= x)
                               && (leftIntersect >= y && leftIntersect < (y + h));

        int     rightIntersect  = point.y + ((point.x - x - w + 1) * vel.y / std::abs(vel.x));
        bool    hitRight        = (point.x >= (x + w) && (point.x + vel.x) < (x + w))
                               && (rightIntersect >= y && rightIntersect < (y + h));

        int     topIntersect    = point.x + ((y - point.y + 1) * vel.x / std::abs(vel.y));
        bool    hitTop          = (point.y < y && (point.y + vel.y) >= y)
                               && (topIntersect >= x && topIntersect < (x + w));

        int     botIntersect    = point.x + ((point.y - y - h + 1) * vel.x / std::abs(vel.y));
        bool    hitBottom       = (point.y >= (y + h) && (point.y + vel.y) < (y + h))
                               && (botIntersect >= x && botIntersect < (x + w));

        if (hitLeft)
        {
            return hitTop ? TopLeft : hitBottom ? BotLeft : Left;
        }
        else if (hitRight)
        {
            return hitTop ? TopRight : hitBottom ? BotRight : Right;
        }
        else
        {
            return hitTop ? Top : hitBottom ? Bot : Miss;
        }
    }
    bool bounce(UI::Pt& point, UI::Pt& velocity) const
    {
        CollisionPoint hit = collision(point, velocity);
        switch (hit)
        {
            case TopLeft:
            case TopRight:
            case BotRight:
            case BotLeft:
                velocity.x = -velocity.x;
                velocity.y = -velocity.y;
                return true;
            case Top:
            case Bot:
                velocity.y = -velocity.y;
                point.x     += velocity.x;
                return true;
            case Right:
            case Left:
                velocity.x = -velocity.x;
                point.y     += velocity.y;
                return true;
            case Miss:
                break;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& s, ThorsAnvil::UI::Rect const& rect)
    {
        return s << "Rect: { {" << rect.x << ", " << rect.y << "} {" << rect.w << ", " << rect.h << "} }";
    }
};

struct Color
{
    Uint8       r;
    Uint8       g;
    Uint8       b;
    Uint8       alpha;

    bool operator==(Color const& rhs) const {return r == rhs.r && g == rhs.g && b == rhs.b && alpha == rhs.alpha;}
    bool operator!=(Color const& rhs) const {return !(*this == rhs);}

    friend std::ostream& operator<<(std::ostream& s, Color const& color)
    {
        return s << "C: {" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g) << ", " << static_cast<int>(color.b) << ", " << static_cast<int>(color.alpha) << "}";
    }
};

namespace C
{
    static constexpr Color  black{0, 0, 0, 255};
    static constexpr Color  silver{192, 192, 192, 255};
    static constexpr Color  gray{128, 128, 128, 255};
    static constexpr Color  white{255, 255, 255, 255};
    static constexpr Color  maroon{128, 0, 0, 255};
    static constexpr Color  red{255, 0, 0, 255};
    static constexpr Color  purple{128, 0, 128, 255};
    static constexpr Color  fuchsia{255, 0, 255, 255};
    static constexpr Color  green{0, 128, 0, 255};
    static constexpr Color  lime{0, 255, 0, 255};
    static constexpr Color  olive{128, 128, 0, 255};
    static constexpr Color  yellow{255, 255, 0, 255};
    static constexpr Color  navy{0, 0, 128, 255};
    static constexpr Color  blue{0, 0, 255, 255};
    static constexpr Color  teal{0, 128, 128, 255};
    static constexpr Color  aqua{0, 255, 255, 255};
    static constexpr Color  aliceblue{240, 248, 255, 255};
    static constexpr Color  antiquewhite{250, 235, 215, 255};
    //aqua  #00ffff 0, 255, 255
    static constexpr Color  aquamarine{127, 255, 212, 255};
    static constexpr Color  azure{240, 255, 255, 255};
    static constexpr Color  beige{245, 245, 220, 255};
    static constexpr Color  bisque{255, 228, 196, 255};
    // black    #000000 0, 0, 0
    static constexpr Color  blanchedalmond{255, 235, 205, 255};
    //blue  #0000ff 0, 0, 255
    static constexpr Color  blueviolet{138, 43, 226, 255};
    static constexpr Color  brown{165, 42, 42, 255};
    static constexpr Color  burlywood{222, 184, 135, 255};
    static constexpr Color  cadetblue{95, 158, 160, 255};
    static constexpr Color  chartreuse{127, 255, 0, 255};
    static constexpr Color  chocolate{210, 105, 30, 255};
    static constexpr Color  coral{255, 127, 80, 255};
    static constexpr Color  cornflowerblue{100, 149, 237, 255};
    static constexpr Color  cornsilk{255, 248, 220, 255};
    static constexpr Color  crimson{220, 20, 60, 255};
    static constexpr Color  cyan{0, 255, 255, 255};
    static constexpr Color  darkblue{0, 0, 139, 255};
    static constexpr Color  darkcyan{0, 139, 139, 255};
    static constexpr Color  darkgoldenrod{184, 134, 11, 255};
    static constexpr Color  darkgray{169, 169, 169, 255};
    static constexpr Color  darkgreen{0, 100, 0, 255};
    static constexpr Color  darkgrey{169, 169, 169, 255};
    static constexpr Color  darkkhaki{189, 183, 107, 255};
    static constexpr Color  darkmagenta{139, 0, 139, 255};
    static constexpr Color  darkolivegreen{85, 107, 47, 255};
    static constexpr Color  darkorange{255, 140, 0, 255};
    static constexpr Color  darkorchid{153, 50, 204, 255};
    static constexpr Color  darkred{139, 0, 0, 255};
    static constexpr Color  darksalmon{233, 150, 122, 255};
    static constexpr Color  darkseagreen{143, 188, 143, 255};
    static constexpr Color  darkslateblue{72, 61, 139, 255};
    static constexpr Color  darkslategray{47, 79, 79, 255};
    static constexpr Color  darkslategrey{47, 79, 79, 255};
    static constexpr Color  darkturquoise{0, 206, 209, 255};
    static constexpr Color  darkviolet{148, 0, 211, 255};
    static constexpr Color  deeppink{255, 20, 147, 255};
    static constexpr Color  deepskyblue{0, 191, 255, 255};
    static constexpr Color  dimgray{105, 105, 105, 255};
    static constexpr Color  dimgrey{105, 105, 105, 255};
    static constexpr Color  dodgerblue{30, 144, 255, 255};
    static constexpr Color  firebrick{178, 34, 34, 255};
    static constexpr Color  floralwhite{255, 250, 240, 255};
    static constexpr Color  forestgreen{34, 139, 34, 255};
    //fuchsia   #ff00ff 255, 0, 255
    static constexpr Color  gainsboro{220, 220, 220, 255};
    static constexpr Color  ghostwhite{248, 248, 255, 255};
    static constexpr Color  gold{255, 215, 0, 255};
    static constexpr Color  goldenrod{218, 165, 32, 255};
    //gray  #808080 128, 128, 128
    //green #008000 0, 128, 0
    static constexpr Color  greenyellow{173, 255, 47, 255};
    static constexpr Color  grey{128, 128, 128, 255};
    static constexpr Color  honeydew{240, 255, 240, 255};
    static constexpr Color  hotpink{255, 105, 180, 255};
    static constexpr Color  indianred{205, 92, 92, 255};
    static constexpr Color  indigo{75, 0, 130, 255};
    static constexpr Color  ivory{255, 255, 240, 255};
    static constexpr Color  khaki{240, 230, 140, 255};
    static constexpr Color  lavender{230, 230, 250, 255};
    static constexpr Color  lavenderblush{255, 240, 245, 255};
    static constexpr Color  lawngreen{124, 252, 0, 255};
    static constexpr Color  lemonchiffon{255, 250, 205, 255};
    static constexpr Color  lightblue{173, 216, 230, 255};
    static constexpr Color  lightcoral{240, 128, 128, 255};
    static constexpr Color  lightcyan{224, 255, 255, 255};
    static constexpr Color  lightgoldenrodyellow{250, 250, 210, 255};
    static constexpr Color  lightgray{211, 211, 211, 255};
    static constexpr Color  lightgreen{144, 238, 144, 255};
    static constexpr Color  lightgrey{211, 211, 211, 255};
    static constexpr Color  lightpink{255, 182, 193, 255};
    static constexpr Color  lightsalmon{255, 160, 122, 255};
    static constexpr Color  lightseagreen{32, 178, 170, 255};
    static constexpr Color  lightskyblue{135, 206, 250, 255};
    static constexpr Color  lightslategray{119, 136, 153, 255};
    static constexpr Color  lightslategrey{119, 136, 153, 255};
    static constexpr Color  lightsteelblue{176, 196, 222, 255};
    static constexpr Color  lightyellow{255, 255, 224, 255};
    //lime  #00ff00 0, 255, 0
    static constexpr Color  limegreen{50, 205, 50, 255};
    static constexpr Color  linen{250, 240, 230, 255};
    static constexpr Color  magenta{255, 0, 255, 255};
    //maroon    #800000 128, 0, 0
    static constexpr Color  mediumaquamarine{102, 205, 170, 255};
    static constexpr Color  mediumblue{0, 0, 205, 255};
    static constexpr Color  mediumorchid{186, 85, 211, 255};
    static constexpr Color  mediumpurple{147, 112, 219, 255};
    static constexpr Color  mediumseagreen{60, 179, 113, 255};
    static constexpr Color  mediumslateblue{123, 104, 238, 255};
    static constexpr Color  mediumspringgreen{0, 250, 154, 255};
    static constexpr Color  mediumturquoise{72, 209, 204, 255};
    static constexpr Color  mediumvioletred{199, 21, 133, 255};
    static constexpr Color  midnightblue{25, 25, 112, 255};
    static constexpr Color  mintcream{245, 255, 250, 255};
    static constexpr Color  mistyrose{255, 228, 225, 255};
    static constexpr Color  moccasin{255, 228, 181, 255};
    static constexpr Color  navajowhite{255, 222, 173, 255};
    //navy  #000080 0, 0, 128
    static constexpr Color  oldlace{253, 245, 230, 255};
    //olive #808000 128, 128, 0
    static constexpr Color  olivedrab{107, 142, 35, 255};
    static constexpr Color  orange{255, 165, 0, 255};
    static constexpr Color  orangered{255, 69, 0, 255};
    static constexpr Color  orchid{218, 112, 214, 255};
    static constexpr Color  palegoldenrod{238, 232, 170, 255};
    static constexpr Color  palegreen{152, 251, 152, 255};
    static constexpr Color  paleturquoise{175, 238, 238, 255};
    static constexpr Color  palevioletred{219, 112, 147, 255};
    static constexpr Color  papayawhip{255, 239, 213, 255};
    static constexpr Color  peachpuff{255, 218, 185, 255};
    static constexpr Color  peru{205, 133, 63, 255};
    static constexpr Color  pink{255, 192, 203, 255};
    static constexpr Color  plum{221, 160, 221, 255};
    static constexpr Color  powderblue{176, 224, 230, 255};
    //purple    #800080 128, 0, 128
    //red   #ff0000 255, 0, 0
    static constexpr Color  rosybrown{188, 143, 143, 255};
    static constexpr Color  royalblue{65, 105, 225, 255};
    static constexpr Color  saddlebrown{139, 69, 19, 255};
    static constexpr Color  salmon{250, 128, 114, 255};
    static constexpr Color  sandybrown{244, 164, 96, 255};
    static constexpr Color  seagreen{46, 139, 87, 255};
    static constexpr Color  seashell{255, 245, 238, 255};
    static constexpr Color  sienna{160, 82, 45, 255};
    //silver    #c0c0c0 192, 192, 192
    static constexpr Color  skyblue{135, 206, 235, 255};
    static constexpr Color  slateblue{106, 90, 205, 255};
    static constexpr Color  slategray{112, 128, 144, 255};
    static constexpr Color  slategrey{112, 128, 144, 255};
    static constexpr Color  snow{255, 250, 250, 255};
    static constexpr Color  springgreen{0, 255, 127, 255};
    static constexpr Color  steelblue{70, 130, 180, 255};
    static constexpr Color  tan{210, 180, 140, 255};
    //teal  #008080 0, 128, 128
    static constexpr Color  thistle{216, 191, 216, 255};
    static constexpr Color  tomato{255, 99, 71, 255};
    static constexpr Color  turquoise{64, 224, 208, 255};
    static constexpr Color  violet{238, 130, 238, 255};
    static constexpr Color  wheat{245, 222, 179, 255};
    //white #ffffff 255, 255, 255
    static constexpr Color  whitesmoke{245, 245, 245, 255};
    //yellow    #ffff00 255, 255, 0
    static constexpr Color  yellowgreen{154, 205, 50, 255};
}


}

#endif
