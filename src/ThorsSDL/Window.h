#ifndef THORSANVIL_UI_WINDOW_H
#define THORSANVIL_UI_WINDOW_H

#include "ThorsSDLConfig.h"
#include "Util.h"
#include <SDL.h>
#include <string>
#include <iostream>

namespace ThorsAnvil::UI
{
/*
Window Flags:
=============
    SDL_WINDOW_FULLSCREEN         fullscreen window
    SDL_WINDOW_FULLSCREEN_DESKTOP fullscreen window at desktop resolution

    SDL_WINDOW_OPENGL             window usable with an OpenGL context
    SDL_WINDOW_VULKAN             window usable with a Vulkan instance
    SDL_WINDOW_METAL              window usable with a Metal instance
    SDL_WINDOW_HIDDEN             window is not visible
    SDL_WINDOW_BORDERLESS         no window decoration
    SDL_WINDOW_RESIZABLE          window can be resized
    SDL_WINDOW_MINIMIZED          window is minimized
    SDL_WINDOW_MAXIMIZED          window is maximized
    SDL_WINDOW_INPUT_GRABBED      window has grabbed input focus
    SDL_WINDOW_ALLOW_HIGHDPI      window should be created in high-DPI mode if supported (>= SDL 2.0.1)
*/


enum WindowType { Default = 0, OpenGL = SDL_WINDOW_OPENGL, Vulkan = SDL_WINDOW_VULKAN, Metal = SDL_WINDOW_METAL };

inline std::ostream& operator<<(std::ostream& s, WindowType const& wt)
{
    switch (wt)
    {
        case Default:   return s << "Default";
        case OpenGL:    return s << "OpenGL";
        case Vulkan:    return s << "Vulkan";
        case Metal:     return s << "Metal";
        default: break;
    }
    return s << "Unknown??";
}

struct WindowState
{
    WindowType  type        = Default;
    bool        fullscreen  = false;
    bool        border      = true;
    bool        resizeable  = true;
    bool        hidden      = false;
    bool        grabFocus   = false;

    operator Uint32 () const;

    friend std::ostream& operator<<(std::ostream& s, WindowState const& ws)
    {
        return s    << "{\n"
                    << "Type:     " << ws.type         << " " << static_cast<Uint32>(ws.type)                 << "\n"
                    << "Full:     " << ws.fullscreen   << " " << (ws.fullscreen ? SDL_WINDOW_FULLSCREEN : 0)  << "\n"
                    << "Border:   " << ws.border       << " " << (ws.border ? 0 : SDL_WINDOW_BORDERLESS)      << "\n"
                    << "Resize:   " << ws.resizeable   << " " << (ws.resizeable ? SDL_WINDOW_RESIZABLE : 0)   << "\n"
                    << "Hidden:   " << ws.hidden       << " " << (ws.hidden ? SDL_WINDOW_HIDDEN : 0)          << "\n"
                    << "Focus:    " << ws.grabFocus    << " " << (ws.grabFocus ? SDL_WINDOW_INPUT_GRABBED : 0)<< "\n"
                    << "Result:   " << static_cast<Uint32>(ws)                                                << "\n"
                    << "}";
    }
};

/*
Renderer Flags:
===============
    SDL_RENDERER_SOFTWARE         The renderer is a software fallback
    SDL_RENDERER_ACCELERATED      The renderer uses hardware acceleration
    SDL_RENDERER_PRESENTVSYNC     Present is synchronized with the refresh rate
    SDL_RENDERER_TARGETTEXTURE    The renderer supports rendering to text
*/

struct RenderState
{
    bool    software    = false;
    bool    accelerated = true;
    bool    presentSync = false;
    bool    targetText  = false;

    operator Uint32 () const;

    friend std::ostream& operator<<(std::ostream& s, RenderState const& rs)
    {
        return s    << "{\n"
                    << "Software:    " << rs.software       << " " << (rs.software ? SDL_RENDERER_SOFTWARE : 0)        << "\n"
                    << "accelerated: " << rs.accelerated    << " " << (rs.accelerated ? SDL_RENDERER_ACCELERATED : 0)  << "\n"
                    << "presentSync: " << rs.presentSync    << " " << (rs.presentSync ? SDL_RENDERER_PRESENTVSYNC : 0) << "\n"
                    << "targetText:  " << rs.targetText     << " " << (rs.targetText ? SDL_RENDERER_TARGETTEXTURE : 0) << "\n"
                    << "}";
    }
};

class Application;

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
        virtual void handleEventWindowUnknown(SDL_WindowEvent const& /*event*/)                 {}

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
        virtual void handleEventKeyMapChanged(SDL_CommonEvent const& /*event*/)                 {}

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& /*event*/)                {}
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& /*event*/)                {}
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& /*event*/)                  {}
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& /*event*/)                {}
};

class Window: public WindowEventHandler
{
    public:
        Window(Application& application, std::string const& title, Rect const& rect, WindowState const& winState = {}, RenderState const& renState = {});
        ~Window();

        Window(Window const&)             = delete;
        Window& operator=(Window const&)  = delete;
        Window(Window&& move) noexcept;
        Window& operator=(Window&& move) noexcept;

        void    draw();
        Uint32  getId() const   {return SDL_GetWindowID(window);}
    private:
        virtual Color   getBackgroundColor() {return {96, 128, 255, 255};}
        virtual void    doDraw();

    private:
        friend class Pen;
        SDL_Renderer* getSurface() const {return renderer;}
    private:
        Application&    application;
        SDL_Window*     window;
        SDL_Renderer*   renderer;
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
        virtual void handleEventWindowUnknown(SDL_WindowEvent const& event) override        {std::cerr << "handleEventWindowUnknown\n";         Window::handleEventWindowUnknown(event);}

    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& event) override            {std::cerr << "handleEventKeyDown\n";               Window::handleEventKeyDown(event);}
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& event) override              {std::cerr << "handleEventKeyUp\n";                 Window::handleEventKeyUp(event);}
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& event) override    {std::cerr << "handleEventTextEditting\n";          Window::handleEventTextEditting(event);}
        virtual void handleEventTextInput(SDL_TextInputEvent const& event) override         {std::cerr << "handleEventTextInput\n";             Window::handleEventTextInput(event);}
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event) override{std::cerr << "handleEventTextEditingExt\n";       Window::handleEventTextEditingExt(event);}
        virtual void handleEventKeyMapChanged(SDL_CommonEvent const& event) override        {std::cerr << "handleEventKeyMapChanged\n";         Window::handleEventKeyMapChanged(event);}

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event) override       {std::cerr << "handleEventMouseMove\n";             Window::handleEventMouseMove(event);}
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& event) override       {std::cerr << "handleEventMouseDown\n";             Window::handleEventMouseDown(event);}
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& event) override         {std::cerr << "handleEventMouseUp\n";               Window::handleEventMouseUp(event);}
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& event) override       {std::cerr << "handleEventMouseWheel\n";            Window::handleEventMouseWheel(event);}
};

}

#endif
