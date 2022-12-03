#ifndef THORSANVIL_UI_VIEW_H
#define THORSANVIL_UI_VIEW_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"

namespace ThorsAnvil::UI
{

class DrawContext;
class View
{
    public:
        virtual ~View();
        virtual void updateState();
        virtual void reset();
        virtual void doDraw(DrawContext& context);
};

}

#endif
