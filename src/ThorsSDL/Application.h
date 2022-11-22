#ifndef THORSANVIL_UI_APPLICATION_H
#define THORSANVIL_UI_APPLICATION_H

#include "ThorsSDLConfig.h"
#include <SDL.h>

namespace ThorsAnvil::UI
{

enum InitValue : Uint32
{
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

class Application
{
    public:
        Application(InitValue init = Everything);
        ~Application();

        Application(Application const&)             = delete;
        Application(Application&&)                  = delete;
        Application& operator=(Application const&)  = delete;
        Application& operator=(Application&&)       = delete;

        void initSubSystem(InitValue init);
        void quitSubSystem(InitValue init);
    private:
        static bool initialized;
};

}

#endif
