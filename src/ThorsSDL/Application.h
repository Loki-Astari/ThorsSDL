#ifndef THORSANVIL_UI_APPLICATION_H
#define THORSANVIL_UI_APPLICATION_H

#include "ThorsSDLConfig.h"
#include "Util.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <functional>
#include <map>

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

struct SDLLibBase
{
    SDLLibBase(int state, char const* message)
    {
        if (state != 0)
        {
            throw std::runtime_error(message);
        }
    }
    virtual ~SDLLibBase()   {}
};

struct SDLLib_Main: public SDLLibBase
{
    SDLLib_Main(InitValue init);
    ~SDLLib_Main();
};

struct SDLLib_TTF: public SDLLibBase
{
    SDLLib_TTF();
    ~SDLLib_TTF();
};

class Window;
class WindowEventHandler;
class Application
{
    private:
        static bool initialized;
        std::unique_ptr<SDLLib_Main>    sdl2;
        std::unique_ptr<SDLLib_TTF>     sdl2ttf;

    private:
        bool                        finished;
        std::map<Uint32, Window*>   windows;
        std::function<void(int)>    userEventDone;


    public:
        Application(InitValue init = Everything, InitLibs = NoLibs);
        Application(InitLibs libs);
        ~Application();

        Application(Application const&)             = delete;
        Application(Application&&)                  = delete;
        Application& operator=(Application const&)  = delete;
        Application& operator=(Application&&)       = delete;

        void initSubSystem(InitValue init);
        void quitSubSystem(InitValue init);

        void initSubSystem(InitLibs libs);
        void quitSubSystem(InitLibs libs);

        void eventLoop(int fps, std::function<void(int)>&& eventDone = [](int){});
        void exitLoop();

    private:
        friend class Window;
        void registerWindow(Window& window);
        void unregisterWindow(Window& window);
        WindowEventHandler& getWindowHander(Uint32 windowId);

    private:
        int handleEvents();
        void updateState(int eventCount);
        void drawWindows();

    protected:
        virtual void handleEventQuit(SDL_QuitEvent const& /*event*/);
        virtual void handleEventTerminating(SDL_CommonEvent const& /*event*/)                   {}
        virtual void handleEventLowMemory(SDL_CommonEvent const& /*event*/)                     {}
        virtual void handleEventBackgroundEnterAboutTo(SDL_CommonEvent const& /*event*/)        {}
        virtual void handleEventBackgroundEnterDone(SDL_CommonEvent const& /*event*/)           {}
        virtual void handleEventForegroundEnterAboutTo(SDL_CommonEvent const& /*event*/)        {}
        virtual void handleEventForegroundEnterDone(SDL_CommonEvent const& /*event*/)           {}
        virtual void handleEventLocalUpdate(SDL_CommonEvent const& /*event*/)                   {}

    /* Display events           0x015*  */
        virtual void handleEventDisplayEvent(SDL_DisplayEvent const& /*event*/)                 {}

    /* Window events            0x020*  */
        virtual void handleEventWindowShow(SDL_WindowEvent const& event);
        virtual void handleEventWindowHide(SDL_WindowEvent const& event);
        virtual void handleEventWindowExpose(SDL_WindowEvent const& event);
        virtual void handleEventWindowMoved(SDL_WindowEvent const& event);
        virtual void handleEventWindowResized(SDL_WindowEvent const& event);
        virtual void handleEventWindowSizeChange(SDL_WindowEvent const& event);
        virtual void handleEventWindowMin(SDL_WindowEvent const& event);
        virtual void handleEventWindowMax(SDL_WindowEvent const& event);
        virtual void handleEventWindowRestore(SDL_WindowEvent const& event);
        virtual void handleEventWindowEnter(SDL_WindowEvent const& event);
        virtual void handleEventWindowLeave(SDL_WindowEvent const& event);
        virtual void handleEventWindowFocusGain(SDL_WindowEvent const& event);
        virtual void handleEventWindowFocusLost(SDL_WindowEvent const& event);
        virtual void handleEventWindowClose(SDL_WindowEvent const& event);
        virtual void handleEventWindowTakeFocus(SDL_WindowEvent const& event);
        virtual void handleEventWindowHitTest(SDL_WindowEvent const& event);
        virtual void handleEventWindowICCProfChange(SDL_WindowEvent const& event);
        virtual void handleEventWindowDisplayChange(SDL_WindowEvent const& event);
        virtual void handleEventWindowUnknown(SDL_WindowEvent const& /*event*/)                 {}
        virtual void handleEventSystemEvent(SDL_SysWMEvent const& /*event*/)                    {}

    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& event);
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& event);
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& event);
        virtual void handleEventTextInput(SDL_TextInputEvent const& event);
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& event);
        virtual void handleEventKeyMapChanged(SDL_CommonEvent const& /*event*/)                 {}

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& event);
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& event);
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& event);
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& event);

    /* Joystick events          0x060*  */
        virtual void handleEventJoyMotion(SDL_JoyAxisEvent const& /*event*/)                    {}
        virtual void handleEventJoyBall(SDL_JoyBallEvent const& /*event*/)                      {}
        virtual void handleEventJoyHat(SDL_JoyHatEvent const& /*event*/)                        {}
        virtual void handleEventJoyButtonDown(SDL_JoyButtonEvent const& /*event*/)              {}
        virtual void handleEventJoyButtonUp(SDL_JoyButtonEvent const& /*event*/)                {}
        virtual void handleEventJoyDeviceAdd(SDL_JoyDeviceEvent const& /*event*/)               {}
        virtual void handleEventJoyDeviceRem(SDL_JoyDeviceEvent const& /*event*/)               {}
        virtual void handleEventJoyBattery(SDL_JoyBatteryEvent const& /*event*/)                {}

    /* Game controller events   0x065*  */
        virtual void handleEventControlMotion(SDL_ControllerAxisEvent const& /*event*/)         {}
        virtual void handleEventControlButtonDown(SDL_ControllerButtonEvent const& /*event*/)   {}
        virtual void handleEventControlButtonUp(SDL_ControllerButtonEvent const& /*event*/)     {}
        virtual void handleEventControlDeviceAdd(SDL_ControllerDeviceEvent const& /*event*/)    {}
        virtual void handleEventControlDeviceRem(SDL_ControllerDeviceEvent const& /*event*/)    {}
        virtual void handleEventControlDeviceMap(SDL_ControllerDeviceEvent const& /*event*/)    {}

        virtual void handleEventTouchPadDown(SDL_ControllerTouchpadEvent const& /*event*/)      {}
        virtual void handleEventTouchPadUp(SDL_ControllerTouchpadEvent const& /*event*/)        {}
        virtual void handleEventTouchPadMotion(SDL_ControllerTouchpadEvent const& /*event*/)    {}
        virtual void handleEventTouchPadSendor(SDL_ControllerSensorEvent const& /*event*/)      {}

    /* Touch events             0x070*  */
        virtual void handleEventFingerDown(SDL_TouchFingerEvent const& /*event*/)               {}
        virtual void handleEventFingerUp(SDL_TouchFingerEvent const& /*event*/)                 {}
        virtual void handleEventFingerMotion(SDL_TouchFingerEvent const& /*event*/)             {}

    /* Gesture events           0x080*  */
        virtual void handleEventDollarGesture(SDL_DollarGestureEvent const& /*event*/)          {}
        virtual void handleEventDollarRecord(SDL_DollarGestureEvent const& /*event*/)           {}
        virtual void handleEventMultiGesture(SDL_MultiGestureEvent const& /*event*/)            {}

    /* Clipboard events         0x09*   */
        virtual void handleEventClipboardUpdate(SDL_CommonEvent const& /*event*/)               {}

    /* Drag and drop events     0x100*  */
        virtual void handleEventDropFile(SDL_DropEvent const& /*event*/)                        {}
        virtual void handleEventDropText(SDL_DropEvent const& /*event*/)                        {}
        virtual void handleEventDropBegin(SDL_DropEvent const& /*event*/)                       {}
        virtual void handleEventDropEnd(SDL_DropEvent const& /*event*/)                         {}

    /* Audio hotplug events     0x110*  */
        virtual void handleEventAudioDeviceAdd(SDL_AudioDeviceEvent const& /*event*/)           {}
        virtual void handleEventAudioDeviceRem(SDL_AudioDeviceEvent const& /*event*/)           {}

    /* Sensor events            0x120*  */
        virtual void handleEventSensorUpdate(SDL_SensorEvent const& /*event*/)                  {}

    /* Render events            0x200*  */
        virtual void handleEventRenderTargetReset(SDL_CommonEvent const& /*event*/)             {}
        virtual void handleEventRenderDeviceReset(SDL_CommonEvent const& /*event*/)             {}

    /* Internal events          0x7F0*  */
        virtual void handleEventPollSentinel(SDL_CommonEvent const& /*event*/)                  {}

    /* User events              0x800*  */
        virtual void handleEventUser(SDL_UserEvent const& /*event*/)                            {}

    /* There is an event we don't know about */
        virtual void handleEventUnknown(SDL_CommonEvent const& /*event*/);

};

}

#endif
