#ifndef THORSANVIL_UI_SPRITE_H
#define THORSANVIL_UI_SPRITE_H

#include "ThorsSDLConfig.h"
#include "DrawContext.h"

namespace ThorsAnvil::UI
{

class Window;
class Sprite: public DrawContext
{
    public:
        Sprite(Window& parent, int millisecondUpdateTime);

    private:
        std::chrono::milliseconds   updatePeriod;
};

}

#endif
