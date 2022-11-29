#ifndef THORSANVIL_UI_SPRITE_H
#define THORSANVIL_UI_SPRITE_H

#include "ThorsSDLConfig.h"
#include "DrawContext.h"
#include "Util.h"

namespace ThorsAnvil::UI
{

class Window;
class Sprite: public DrawContext
{
    Window&             parent;
    TimePoint           lastUpdate;
    int                 updatePeriod;

    public:
        Sprite(Window& parent, std::size_t layer, int millisecondUpdateTime);
        virtual ~Sprite();

        void updateState();

        virtual void doDraw(DrawContext& drawContext)   = 0;
        virtual bool doUpdateState()                    = 0;
};

}

#endif
