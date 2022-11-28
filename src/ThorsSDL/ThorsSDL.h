#ifndef THORSANVIL_UI_THORS_SDL_H
#define THORSANVIL_UI_THORS_SDL_H

#include "ThorsSDLConfig.h"
#include <SDL.h>
#include <SDL_ttf.h>

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
    NoLibs  = 0,
    Fonts   = 1,
    Images  = 2
};

inline InitLibs operator|(InitLibs lhs, InitLibs rhs)
{
    return static_cast<InitLibs>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
}

inline bool operator&(InitLibs lhs, InitLibs rhs)
{
    return (static_cast<Uint32>(lhs) & static_cast<Uint32>(rhs)) != 0;
}

namespace SDL
{

struct BaseWrapper
{
    BaseWrapper(int state, char const* message)
    {
        if (state != 0)
        {
            throw std::runtime_error(message);
        }
    }
    virtual ~BaseWrapper()   = 0;

    BaseWrapper(BaseWrapper const&)               = delete;
    BaseWrapper(BaseWrapper&&)                    = delete;
    BaseWrapper& operator=(BaseWrapper const&)    = delete;
    BaseWrapper& operator=(BaseWrapper&&)         = delete;
};

template<typename T>
struct PointerWrapper: public BaseWrapper
{
    T*      pointer;
    PointerWrapper(T* pointer, char const* message)
        : BaseWrapper(pointer == nullptr ? -1 : 0, message)
        , pointer(pointer)
    {}
    virtual ~PointerWrapper()   = 0;

    operator T*()
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

}
}

#endif
