#ifndef THORSANVIL_UI_VIEW_H
#define THORSANVIL_UI_VIEW_H

#include "ThorsSDLConfig.h"
#include "WindowEventHandler.h"
#include "Util.h"

namespace ThorsAnvil::UI
{

class Window;
class DrawContext;
class View: public WindowEventHandler
{
    protected:
        Window& parent;
    public:
        View(Window& parent);
        virtual ~View();
        virtual void updateState();
        virtual Sz reset();
        virtual void draw(DrawContext& context);

        DrawContext& getDrawContext();
};

}

#endif
