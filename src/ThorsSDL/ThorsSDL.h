#ifndef THORSANVIL_UI_THORS_SDL_H
#define THORSANVIL_UI_THORS_SDL_H

#include "ThorsSDLConfig.h"
#include <SDL.h>

namespace ThorsAnvil::UI
{

enum InitValue : Uint32  {
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

InitValue operator|(InitValue lhs, InitValue rhs)
{
    return static_cast<InitValue>(static_cast<Uint32>(lhs) | static_cast<Uint32>(rhs));
}

class ThorSDL
{
    public:
        ThorSDL(InitValue init = Everything);
        ~ThorSDL();

        ThorSDL(ThorSDL const&)             = delete;
        ThorSDL(ThorSDL&&)                  = delete;
        ThorSDL& operator=(ThorSDL const&)  = delete;
        ThorSDL& operator=(ThorSDL&&)       = delete;

        void initSubSystem(InitValue init);
        void quitSubSystem(InitValue init);
    private:
        static bool initialized;
};

}

#endif
