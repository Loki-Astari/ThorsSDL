#ifndef THORSANVIL_UI_SURFACE_H
#define THORSANVIL_UI_SURFACE_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"
//#include "Util.h"
//#include <gtest/gtest_prod.h>
//#include <memory>

namespace ThorsAnvil::UI
{

class Surface
{
    SDL::Surface    surface;
    public:
        Surface()
            :
        Surface(SDL::Surface&& surface)
            : surface(std::move(surface))
        {}

        friend std::istream& operator>>(std::istream& stream, Surface& dst)
};

}

#endif
