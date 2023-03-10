#ifndef THORSANVIL_UI_THORS_SDL_H
#define THORSANVIL_UI_THORS_SDL_H

#include "ThorsSDLConfig.h"
#include "Util.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

namespace ThorsAnvil::UI
{

enum InitValue : Uint32
{
    Nothing = 0,
    Timer = SDL_INIT_TIMER,
    Audio = SDL_INIT_AUDIO,
    Video = SDL_INIT_VIDEO,
    //CDRom = SDL_INIT_CDROM,
    JoyStick = SDL_INIT_JOYSTICK,
    Haptic = SDL_INIT_HAPTIC,
    Controller = SDL_INIT_GAMECONTROLLER,
    Events  = SDL_INIT_EVENTS,
    Sensor = SDL_INIT_SENSOR,
    Everything = SDL_INIT_EVERYTHING,       // || of the above values.
    NoParachute = SDL_INIT_NOPARACHUTE,     // Prevents SDL from catching fatal signals.
};

inline InitValue operator|(InitValue lhs, InitValue rhs)
{
    return static_cast<InitValue>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
}

enum InitLibs : Uint32
{
    NoLibs      = 0,
    Fonts       = 1,
    ImageJpg    = 2,    // IMG_INIT_JPG
    ImagePng    = 4,    // IMG_INIT_PNG
    ImageTif    = 8,    // IMG_INIT_TIF
    ImageWebp   = 16,   // IMG_INIT_WEBP
    ImageJxl    = 32,   // IMG_INIT_JXL
    ImageAvif   = 64,   // IMG_INIT_AVIF
    Images      = ImageJpg | ImagePng | ImageTif | ImageWebp | ImageJxl | ImageAvif
};

inline InitLibs operator|(InitLibs lhs, InitLibs rhs)
{
    return static_cast<InitLibs>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
}

inline bool operator&(InitLibs lhs, InitLibs rhs)
{
    return (static_cast<Uint32>(lhs) & static_cast<Uint32>(rhs)) != 0;
}

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


namespace SDL
{

struct BaseWrapper
{
    BaseWrapper(int state, char const* message)
    {
        if (state != 0) {
            throw std::runtime_error(message);
        }
    }
    virtual ~BaseWrapper()   = 0;

    BaseWrapper(BaseWrapper const&)               = delete;
    BaseWrapper(BaseWrapper&&)                    = default;
    BaseWrapper& operator=(BaseWrapper const&)    = delete;
    BaseWrapper& operator=(BaseWrapper&&)         = default;
};

template<typename T>
struct PointerWrapper: public BaseWrapper
{
    T*      pointer;
    PointerWrapper()
        : BaseWrapper(0, "")
        , pointer(nullptr)
    {}
    PointerWrapper(T* pointer, char const* message)
        : BaseWrapper(pointer == nullptr ? -1 : 0, message)
        , pointer(pointer)
    {}
    PointerWrapper(PointerWrapper&& src) noexcept
        : BaseWrapper(std::move(src))
        , pointer(std::exchange(src.pointer, nullptr))
    {}
    PointerWrapper& operator=(PointerWrapper&& src) noexcept
    {
        std::swap(pointer, src.pointer);
        return *this;
    }

    void swap(PointerWrapper& other) noexcept
    {
        std::swap(pointer, other.pointer);
    }
    friend void swap(PointerWrapper& lhs, PointerWrapper& rhs)   {lhs.swap(rhs);}

    operator T*() const
    {
        return pointer;
    }
};

struct Lib_Main: public BaseWrapper
{
    Lib_Main(InitValue init);
    ~Lib_Main();
};

struct Lib_TTF: public BaseWrapper
{
    Lib_TTF();
    ~Lib_TTF();
};

struct Lib_Image: public BaseWrapper
{
    Lib_Image(InitLibs init);
    ~Lib_Image();

    static int initialize(InitLibs init);
};

struct Window: public PointerWrapper<SDL_Window>
{
    Window(std::string const& title, Rect const& rect, WindowState const& winState);
    ~Window();
};

struct Renderer: public PointerWrapper<SDL_Renderer>
{
    Renderer(SDL_Window* sdlWindow, RenderState const& renState);
    ~Renderer();
};

struct TTFont: public PointerWrapper<TTF_Font>
{
    TTFont(std::string const& fileName, int point);
    ~TTFont();

    int ascent()                        const   {return TTF_FontAscent(pointer);}
    int descent()                       const   {return TTF_FontDescent(pointer);}
    int height()                        const   {return TTF_FontHeight(pointer);}       // Usually equal to point size
    int lineSkip()                      const   {return TTF_FontLineSkip(pointer);}     // The recommended line size (how far to move down for next line)
    int length(std::string const& view) const   {int w, h;TTF_SizeUTF8(pointer, view.c_str(), &w, &h);return w;}
};

struct Surface: public PointerWrapper<SDL_Surface>
{
    Surface();
    Surface(SDL_Surface* surface, char const* message = "Invalid NullPtr passed to Surface cretion");
    Surface(Surface&& src) noexcept             = default;
    Surface& operator=(Surface&& rc) noexcept   = default;
    ~Surface();
};

}
}

#endif
