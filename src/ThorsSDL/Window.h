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
    bool        focus       = true;

    operator Uint32 () const;

    friend std::ostream& operator<<(std::ostream& s, WindowState const& ws)
    {
        return s    << "{\n"
                    << "Type:     " << ws.type         << " " << static_cast<Uint32>(ws.type)                 << "\n"
                    << "Full:     " << ws.fullscreen   << " " << (ws.fullscreen ? SDL_WINDOW_FULLSCREEN : 0)  << "\n"
                    << "Border:   " << ws.border       << " " << (ws.border ? 0 : SDL_WINDOW_BORDERLESS)      << "\n"
                    << "Resize:   " << ws.resizeable   << " " << (ws.resizeable ? SDL_WINDOW_RESIZABLE : 0)   << "\n"
                    << "Hidden:   " << ws.hidden       << " " << (ws.hidden ? SDL_WINDOW_HIDDEN : 0)          << "\n"
                    << "Focus:    " << ws.focus        << " " << (ws.focus ? SDL_WINDOW_INPUT_GRABBED : 0)    << "\n"
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
class Window
{
    public:
        Window(Application& application, std::string const& title, Rect const& rect, WindowState const& winState = {}, RenderState const& renState = {});
        ~Window();

        Window(Window const&)             = delete;
        Window& operator=(Window const&)  = delete;
        Window(Window&& move) noexcept;
        Window& operator=(Window&& move) noexcept;

        void draw();

    private:
        friend class Application;
        Application&    application;
        SDL_Window*     window;
        SDL_Renderer*   renderer;
};

}

#endif
