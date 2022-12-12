#ifndef THORSANVIL_UI_SPRITE_H
#define THORSANVIL_UI_SPRITE_H

#include "ThorsGraphicsConfig.h"
#include "View.h"
#include "ThorsUI/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Graphics
{

namespace UI = ThorsAnvil::UI;

class View;
class Sprite
{
    View&               parent;
    UI::TimePoint       lastUpdate;
    int                 updatePeriod;

    public:
        Sprite(View& parent, int millisecondUpdateTime);
        virtual ~Sprite();

        void updateState();

        virtual void draw(UI::DrawContext& drawContext)     = 0;
        virtual bool doUpdateState()                        = 0;
        virtual void reset();
};

}

#endif
