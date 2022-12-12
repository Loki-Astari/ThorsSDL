#ifndef THORSANVIL_UI_WINDOW_EVENT_HANDLER_H
#define THORSANVIL_UI_WINDOW_EVENT_HANDLER_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"


namespace ThorsAnvil::UI
{

class WindowEventHandler
{
    public:
    /* Window events            0x020*  */
        virtual void handleEventWindowShow(SDL_WindowEvent const& /*event*/)                    {}
        virtual void handleEventWindowHide(SDL_WindowEvent const& /*event*/)                    {}
        virtual void handleEventWindowExpose(SDL_WindowEvent const& /*event*/)                  {}
        virtual void handleEventWindowMoved(SDL_WindowEvent const& /*event*/)                   {}
        virtual void handleEventWindowResized(SDL_WindowEvent const& /*event*/)                 {}
        virtual void handleEventWindowSizeChange(SDL_WindowEvent const& /*event*/)              {}
        virtual void handleEventWindowMin(SDL_WindowEvent const& /*event*/)                     {}
        virtual void handleEventWindowMax(SDL_WindowEvent const& /*event*/)                     {}
        virtual void handleEventWindowRestore(SDL_WindowEvent const& /*event*/)                 {}
        virtual void handleEventWindowEnter(SDL_WindowEvent const& /*event*/)                   {}
        virtual void handleEventWindowLeave(SDL_WindowEvent const& /*event*/)                   {}
        virtual void handleEventWindowFocusGain(SDL_WindowEvent const& /*event*/)               {}
        virtual void handleEventWindowFocusLost(SDL_WindowEvent const& /*event*/)               {}
        virtual void handleEventWindowClose(SDL_WindowEvent const& /*event*/)                   {}
        virtual void handleEventWindowTakeFocus(SDL_WindowEvent const& /*event*/)               {}
        virtual void handleEventWindowHitTest(SDL_WindowEvent const& /*event*/)                 {}
        virtual void handleEventWindowICCProfChange(SDL_WindowEvent const& /*event*/)           {}
        virtual void handleEventWindowDisplayChange(SDL_WindowEvent const& /*event*/)           {}

    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& /*event*/)                     {}
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& /*event*/)                       {}
            // SDL_KeyboardEvent:
            //  Uint8       state
            //  Uint8       repeat
            //  SDL_Keysym  keysym
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& /*event*/)             {}
        virtual void handleEventTextInput(SDL_TextInputEvent const& /*event*/)                  {}
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& /*event*/)        {}

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& /*event*/)                {}
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& /*event*/)                {}
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& /*event*/)                  {}
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& /*event*/)                {}
};


}

#endif
