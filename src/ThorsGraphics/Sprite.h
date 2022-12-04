#ifndef THORSANVIL_UI_SPRITE_H
#define THORSANVIL_UI_SPRITE_H

#include "ThorsGraphicsConfig.h"
#include "GraphicView.h"
#include "ThorsSDL/Util.h"

namespace ThorsAnvil::UI
{
    class DrawContext;
}

namespace ThorsAnvil::Graphics
{

class GraphicView;
class Sprite
{
    GraphicView&        parent;
    UI::TimePoint       lastUpdate;
    int                 updatePeriod;

    public:
        Sprite(GraphicView& parent, int millisecondUpdateTime);
        virtual ~Sprite();

        void updateState();

        virtual void doDraw(UI::DrawContext& drawContext)   = 0;
        virtual bool doUpdateState()                        = 0;
        virtual void reset();
};

}

#endif
