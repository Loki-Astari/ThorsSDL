#ifndef THORSANVIL_UI_WINDOW_H
#define THORSANVIL_UI_WINDOW_H

#include "ThorsSDLConfig.h"
#include "ThorsSDL.h"
#include "DrawContext.h"
#include <gtest/gtest_prod.h>
#include <string>
#include <iostream>
#include <vector>

class SpriteTest_WindowConstruction_Test;
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

class WindowRegister
{
    Window&         window;
    public:
        WindowRegister(Window& window);
        ~WindowRegister();
};

class Application;
class Sprite;
class Window: public WindowEventHandler, public DrawContext
{
    public:
        Window(Application& application, std::string const& title, Rect const& rect, WindowState const& winState = {}, RenderState const& renState = {});
        ~Window();

        Window(Window const&)             = delete;
        Window& operator=(Window const&)  = delete;
        Window(Window&& move) noexcept;
        Window& operator=(Window&& move) noexcept;

    public:
        void    updateState();
        void    draw();
        Uint32  getId() const;

    private:
        virtual Color   getBackgroundColor() {return {96, 128, 255, 255};}

    private:
        friend class Sprite;
        void    addSprite(Sprite& sprite, std::size_t layer);
        void    remSprite(Sprite& sprite);

    private:
        friend class WindowRegister;
        void registerWindow();
        void unregisterWindow();

    private:
        FRIEND_TEST(::SpriteTest, WindowConstruction);

    private:
        Application&                        application;
        std::unique_ptr<SDL::Window>        window;
        WindowRegister                      windowRegister;
        std::vector<std::vector<Sprite*>>   sprites;
        std::size_t                         currentSpriteLayer;
};

class DebugWindow: public Window
{
    public:
        using Window::Window;

    /* Window events            0x020*  */
        virtual void handleEventWindowShow(SDL_WindowEvent const& event) override           {std::cerr << "handleEventWindowShow\n";            Window::handleEventWindowShow(event);}
        virtual void handleEventWindowHide(SDL_WindowEvent const& event) override           {std::cerr << "handleEventWindowHide\n";            Window::handleEventWindowHide(event);}
        virtual void handleEventWindowExpose(SDL_WindowEvent const& event) override         {std::cerr << "handleEventWindowExpose\n";          Window::handleEventWindowExpose(event);}
        virtual void handleEventWindowMoved(SDL_WindowEvent const& event) override          {std::cerr << "handleEventWindowMoved\n";           Window::handleEventWindowMoved(event);}
        virtual void handleEventWindowResized(SDL_WindowEvent const& event) override        {std::cerr << "handleEventWindowResized\n";         Window::handleEventWindowResized(event);}
        virtual void handleEventWindowSizeChange(SDL_WindowEvent const& event) override     {std::cerr << "handleEventWindowSizeChange\n";      Window::handleEventWindowSizeChange(event);}
        virtual void handleEventWindowMin(SDL_WindowEvent const& event) override            {std::cerr << "handleEventWindowMin\n";             Window::handleEventWindowMin(event);}
        virtual void handleEventWindowMax(SDL_WindowEvent const& event) override            {std::cerr << "handleEventWindowMax\n";             Window::handleEventWindowMax(event);}
        virtual void handleEventWindowRestore(SDL_WindowEvent const& event) override        {std::cerr << "handleEventWindowRestore\n";         Window::handleEventWindowRestore(event);}
        virtual void handleEventWindowEnter(SDL_WindowEvent const& event) override          {std::cerr << "handleEventWindowEnter\n";           Window::handleEventWindowEnter(event);}
        virtual void handleEventWindowLeave(SDL_WindowEvent const& event) override          {std::cerr << "handleEventWindowLeave\n";           Window::handleEventWindowLeave(event);}
        virtual void handleEventWindowFocusGain(SDL_WindowEvent const& event) override      {std::cerr << "handleEventWindowFocusGain\n";       Window::handleEventWindowFocusGain(event);}
        virtual void handleEventWindowFocusLost(SDL_WindowEvent const& event) override      {std::cerr << "handleEventWindowFocusLost\n";       Window::handleEventWindowFocusLost(event);}
        virtual void handleEventWindowClose(SDL_WindowEvent const& event) override          {std::cerr << "handleEventWindowClose\n";           Window::handleEventWindowClose(event);}
        virtual void handleEventWindowTakeFocus(SDL_WindowEvent const& event) override      {std::cerr << "handleEventWindowTakeFocus\n";       Window::handleEventWindowTakeFocus(event);}
        virtual void handleEventWindowHitTest(SDL_WindowEvent const& event) override        {std::cerr << "handleEventWindowHitTest\n";         Window::handleEventWindowHitTest(event);}
        virtual void handleEventWindowICCProfChange(SDL_WindowEvent const& event) override  {std::cerr << "handleEventWindowICCProfChange\n";   Window::handleEventWindowICCProfChange(event);}
        virtual void handleEventWindowDisplayChange(SDL_WindowEvent const& event) override  {std::cerr << "handleEventWindowDisplayChange\n";   Window::handleEventWindowDisplayChange(event);}

    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& event) override            {std::cerr << "handleEventKeyDown\n";               Window::handleEventKeyDown(event);}
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& event) override              {std::cerr << "handleEventKeyUp\n";                 Window::handleEventKeyUp(event);}
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& event) override    {std::cerr << "handleEventTextEditting\n";          Window::handleEventTextEditting(event);}
        virtual void handleEventTextInput(SDL_TextInputEvent const& event) override         {std::cerr << "handleEventTextInput\n";             Window::handleEventTextInput(event);}
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event) override{std::cerr << "handleEventTextEditingExt\n";       Window::handleEventTextEditingExt(event);}

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event) override       {std::cerr << "handleEventMouseMove\n";             Window::handleEventMouseMove(event);}
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& event) override       {std::cerr << "handleEventMouseDown\n";             Window::handleEventMouseDown(event);}
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& event) override         {std::cerr << "handleEventMouseUp\n";               Window::handleEventMouseUp(event);}
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& event) override       {std::cerr << "handleEventMouseWheel\n";            Window::handleEventMouseWheel(event);}
};

}

#endif
