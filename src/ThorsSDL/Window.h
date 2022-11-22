#ifndef THORSANVIL_UI_WINDOW_H
#define THORSANVIL_UI_WINDOW_H


#include "ThorsSDLConfig.h"
#include <SDL.h>
#include <string>
#include <iostream>

namespace ThorsAnvil::UI
{


struct Rect
{
    int         x;
    int         y;
    int         w;
    int         h;

    friend std::ostream& operator<<(std::ostream& s, Rect const& rect)
    {
        return s << "R: { {" << rect.x << ", " << rect.y << "} {" << rect.w << ", " << rect.h << "} }";
    }
};

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
    bool        border      = true;
    bool        resizeable  = true;
    bool        hidden      = false;
    bool        focus       = true;

    operator Uint32 () const;

    friend std::ostream& operator<<(std::ostream& s, WindowState const ws)
    {
        return s    << "{\n"
                    << "Type:     " << ws.type         << " " << static_cast<Uint32>(ws.type)                 << "\n"
                    << "Border:   " << ws.border       << " " << (ws.border ? 0 : SDL_WINDOW_BORDERLESS)      << "\n"
                    << "Resize:   " << ws.resizeable   << " " << (ws.resizeable ? SDL_WINDOW_RESIZABLE : 0)   << "\n"
                    << "Hidden:   " << ws.hidden       << " " << (ws.hidden ? SDL_WINDOW_HIDDEN : 0)          << "\n"
                    << "Focus:    " << ws.focus        << " " << (ws.focus ? SDL_WINDOW_INPUT_GRABBED : 0)    << "\n"
                    << "Result:   " << static_cast<Uint32>(ws)                                                << "\n"
                    << "}";
    }
};

class Window
{
    public:
        Window(std::string const& title, Rect const& rect, WindowState state);
        ~Window();

        Window(Window const&)             = delete;
        Window& operator=(Window const&)  = delete;
        Window(Window&& move) noexcept;
        Window& operator=(Window&& move) noexcept;

    private:
        SDL_Window*     window;
};

}

#endif
