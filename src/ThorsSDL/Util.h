#ifndef THORSANVIL_UI_UTIL_H
#define THORSANVIL_UI_UTIL_H

#include "ThorsSDLConfig.h"
#include <SDL.h>
#include <iostream>

namespace ThorsAnvil::UI
{

static constexpr int windowUndefinedPos = SDL_WINDOWPOS_UNDEFINED;
static constexpr int windowCentered     = SDL_WINDOWPOS_CENTERED;

struct Rect
{
    int         x;
    int         y;
    int         w;
    int         h;

    friend std::ostream& operator<<(std::ostream& s, Rect const& rect)
    {
        return s << "R: { {" << rect.x << ", " << rect.y << "} {" << rect.w << ", " << rect.h << "} }";
    }
};

struct Color
{
    Uint8       r;
    Uint8       g;
    Uint8       b;
    Uint8       alpha;

    friend std::ostream& operator<<(std::ostream& s, Color const& color)
    {
        return s << "C: { {" << color.r << ", " << color.g << ", " << color.b << ", " << color.alpha << "} }";
    }
};


}

#endif
