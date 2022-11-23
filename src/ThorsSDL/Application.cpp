#include "Application.h"
#include "Window.h"
#include <stdexcept>
#include <iostream>


using namespace ThorsAnvil::UI;

bool Application::initialized = false;

Application::Application(InitValue init)
    : finished(false)
{
    if (initialized)
    {
        throw std::runtime_error("Attempt to re-initialize SDL");
    }
    auto result = SDL_Init(static_cast<Uint32>(init));
    if (result != 0)
    {
        throw std::runtime_error("Failed to initialize SDL");
    }
    initialized = true;
}

Application::~Application()
{
    SDL_Quit();
}

void Application::initSubSystem(InitValue init)
{
    auto result = SDL_InitSubSystem(static_cast<Uint32>(init));
    if (result != 0)
    {
        throw std::runtime_error("Failed to init sub system");
    }
}

void Application::quitSubSystem(InitValue init)
{
    SDL_QuitSubSystem(static_cast<Uint32>(init));
}

void Application::eventLoop(std::function<void()>&& action)
{
    try
    {
        while (!finished)
        {
            handleEvents();
            drawWindows();
            action();
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void Application::exitLoop()
{
    finished    = true;
}

void Application::registerWindow(Window& window)
{
    windows[window.window] = &window;
}

void Application::unregisterWindow(Window& window)
{
    windows.erase(windows.find(window.window));
}

void Application::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
    /* Application events       0x010*  */
            case SDL_QUIT:                      return handleEventQuit(event.quit);                 // SDL_QuitEvent
            case SDL_APP_TERMINATING:           return handleEventTerminating(event.common);        // SDL_CommonEvent
            case SDL_APP_LOWMEMORY:             return handleEventLowMemory(event.common);          // SDL_CommonEvent
            case SDL_APP_WILLENTERBACKGROUND:   return handleEventBackground(event.common, false);  // SDL_CommonEvent
            case SDL_APP_DIDENTERBACKGROUND:    return handleEventBackground(event.common, true);   // SDL_CommonEvent
            case SDL_APP_WILLENTERFOREGROUND:   return handleEventForeground(event.common, false);  // SDL_CommonEvent
            case SDL_APP_DIDENTERFOREGROUND:    return handleEventForeground(event.common, true);   // SDL_CommonEvent
            case SDL_LOCALECHANGED:             return handleEventLocalUpdate(event.common);        // SDL_CommonEvent

    /* Display events           0x015*  */
            case SDL_DISPLAYEVENT:              return handleEventDisplayEvent(event.display);      // SDL_DisplayEvent

    /* Window events            0x020*  */
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_SHOWN:             return handleEventWindowShow(event.window);             // SDL_WindowEventzz
                    case SDL_WINDOWEVENT_HIDDEN:            return handleEventWindowHide(event.window);             // SDL_WindowEventz
                    case SDL_WINDOWEVENT_EXPOSED:           return handleEventWindowExpose(event.window);           // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MOVED:             return handleEventWindowMmoved(event.window);           // SDL_WindowEvent
                    case SDL_WINDOWEVENT_RESIZED:           return handleEventWindowResized(event.window);          // SDL_WindowEvent
                    case SDL_WINDOWEVENT_SIZE_CHANGED:      return handleEventWindowSizeChange(event.window);       // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MINIMIZED:         return handleEventWindowMin(event.window);              // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MAXIMIZED:         return handleEventWindowMax(event.window);              // SDL_WindowEvent
                    case SDL_WINDOWEVENT_RESTORED:          return handleEventWindowRestore(event.window);          // SDL_WindowEvent
                    case SDL_WINDOWEVENT_ENTER:             return handleEventWindowEnter(event.window);            // SDL_WindowEvent
                    case SDL_WINDOWEVENT_LEAVE:             return handleEventWindowLeave(event.window);            // SDL_WindowEvent
                    case SDL_WINDOWEVENT_FOCUS_GAINED:      return handleEventWindowFocusGain(event.window);        // SDL_WindowEvent
                    case SDL_WINDOWEVENT_FOCUS_LOST:        return handleEventWindowFocusLost(event.window);        // SDL_WindowEvent
                    case SDL_WINDOWEVENT_CLOSE:             return handleEventWindowClose(event.window);            // SDL_WindowEvent
                    case SDL_WINDOWEVENT_TAKE_FOCUS:        return handleEventWindowTakeFocus(event.window);        // SDL_WindowEvent
                    case SDL_WINDOWEVENT_HIT_TEST:          return handleEventWindowHitTest(event.window);          // SDL_WindowEvent
                    case SDL_WINDOWEVENT_ICCPROF_CHANGED:   return handleEventWindowICCProfChange(event.window);    // SDL_WindowEvent
                    case SDL_WINDOWEVENT_DISPLAY_CHANGED:   return handleEventWindowDisplayChange(event.window);    // SDL_WindowEvent
                    default:    return handleEventWindowUnknown(event.window);                                      // SDL_WindowEvent
                }
            }
            case SDL_SYSWMEVENT:                return handleEventSystemEvent(event.syswm);         // SDL_SysWMEvent

    /* Keyboard events          0x030*  */
            case SDL_KEYDOWN:                   return handleEventKeyDown(event.key);               // SDL_KeyboardEvent
            case SDL_KEYUP:                     return handleEventKeyUp(event.key);                 // SDL_KeyboardEvent
            case SDL_TEXTEDITING:               return handleEventTextEditting(event.edit);         // SDL_TextEditingEvent
            case SDL_TEXTINPUT:                 return handleEventTextInput(event.text);            // SDL_TextInputEvent
            case SDL_KEYMAPCHANGED:             return handleEventKeyMapChanged(event.common);      // SDL_CommonEvent
            case SDL_TEXTEDITING_EXT:           return handleEventTextEditingExt(event.editExt);    // SDL_TextEditingExtEvent

    /* Mouse events             0x040*  */
            case SDL_MOUSEMOTION:               return handleEventMouseMove(event.motion);          // SDL_MouseMotionEvent
            case SDL_MOUSEBUTTONDOWN:           return handleEventMouseDown(event.button);          // SDL_MouseButtonEvent
            case SDL_MOUSEBUTTONUP:             return handleEventMouseUp(event.button);            // SDL_MouseButtonEvent
            case SDL_MOUSEWHEEL:                return handleEventMouseWheel(event.wheel);          // SDL_MouseWheelEvent

    /* Joystick events          0x060*  */
            case SDL_JOYAXISMOTION:             return handleEventJoyMotion(event.jaxis);           // SDL_JoyAxisEvent
            case SDL_JOYBALLMOTION:             return handleEventJoyBall(event.jball);             // SDL_JoyBallEvent
            case SDL_JOYHATMOTION:              return handleEventJoyHat(event.jhat);               // SDL_JoyHatEvent
            case SDL_JOYBUTTONDOWN:             return handleEventJoyButtonDown(event.jbutton);     // SDL_JoyButtonEvent
            case SDL_JOYBUTTONUP:               return handleEventJoyButtonUp(event.jbutton);       // SDL_JoyButtonEvent
            case SDL_JOYDEVICEADDED:            return handleEventJoyDeviceAdd(event.jdevice);      // SDL_JoyDeviceEvent
            case SDL_JOYDEVICEREMOVED:          return handleEventJoyDeviceRem(event.jdevice);      // SDL_JoyDeviceEvent
            case SDL_JOYBATTERYUPDATED:         return handleEventJoyBattery(event.jbattery);       // SDL_JoyBatteryEvent

    /* Game controller events   0x065*  */
            case SDL_CONTROLLERAXISMOTION:      return handleEventControlMotion(event.caxis);       // SDL_ControllerAxisEvent
            case SDL_CONTROLLERBUTTONDOWN:      return handleEventControlButtonDown(event.cbutton); // SDL_ControllerButtonEvent
            case SDL_CONTROLLERBUTTONUP:        return handleEventControlButtonUp(event.cbutton);   // SDL_ControllerButtonEvent
            case SDL_CONTROLLERDEVICEADDED:     return handleEventControlDeviceAdd(event.cdevice);  // SDL_ControllerDeviceEvent
            case SDL_CONTROLLERDEVICEREMOVED:   return handleEventControlDeviceRem(event.cdevice);  // SDL_ControllerDeviceEvent
            case SDL_CONTROLLERDEVICEREMAPPED:  return handleEventControlDeviceMap(event.cdevice);  // SDL_ControllerDeviceEvent

            case SDL_CONTROLLERTOUCHPADDOWN:    return handleEventTouchPadDown(event.ctouchpad);    // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERTOUCHPADUP:      return handleEventTouchPadUp(event.ctouchpad);      // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERTOUCHPADMOTION:  return handleEventTouchPadMotion(event.ctouchpad);  // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERSENSORUPDATE:    return handleEventTouchPadSendor(event.csensor);    // SDL_ControllerSensorEvent

    /* Touch events             0x070*  */
            case SDL_FINGERDOWN:                return handleEventFingerDown(event.tfinger);        // SDL_TouchFingerEvent
            case SDL_FINGERUP:                  return handleEventFingerUp(event.tfinger);          // SDL_TouchFingerEvent
            case SDL_FINGERMOTION:              return handleEventFingerMotion(event.tfinger);      // SDL_TouchFingerEvent

    /* Gesture events           0x080*  */
            case SDL_DOLLARGESTURE:             return handleEventDollarGesture(event.dgesture);    // SDL_DollarGestureEvent
            case SDL_DOLLARRECORD:              return handleEventDollarRecord(event.dgesture);     // SDL_DollarGestureEvent
            case SDL_MULTIGESTURE:              return handleEventMultiGesture(event.mgesture);     // SDL_MultiGestureEvent

    /* Clipboard events         0x09*   */
            case SDL_CLIPBOARDUPDATE:           return handleEventClipboardUpdate(event.common);    // SDL_CommonEvent

    /* Drag and drop events     0x100*  */
            case SDL_DROPFILE:                  return handleEventDropFile(event.drop);             // SDL_DropEvent
            case SDL_DROPTEXT:                  return handleEventDropText(event.drop);             // SDL_DropEvent
            case SDL_DROPBEGIN:                 return handleEventDropBegin(event.drop);            // SDL_DropEvent
            case SDL_DROPCOMPLETE:              return handleEventDropEnd(event.drop);              // SDL_DropEvent

    /* Audio hotplug events     0x110*  */
            case SDL_AUDIODEVICEADDED:          return handleEventAudioDeviceAdd(event.adevice);    // SDL_AudioDeviceEvent
            case SDL_AUDIODEVICEREMOVED:        return handleEventAudioDeviceRem(event.adevice);    // SDL_AudioDeviceEvent

    /* Sensor events            0x120*  */
            case SDL_SENSORUPDATE:              return handleEventSensorUpdate(event.sensor);       // SDL_SensorEvent

    /* Render events            0x200*  */
            case SDL_RENDER_TARGETS_RESET:      return handleEventRenderTargetReset(event.common);  // SDL_CommonEvent
            case SDL_RENDER_DEVICE_RESET:       return handleEventRenderDeviceReset(event.common);  // SDL_CommonEvent

    /* Internal events          0x7F0*  */
            case SDL_POLLSENTINEL:              return handleEventPollSentinel(event.common);       // SDL_CommonEvent

    /* User events              0x800*  */
            case SDL_USEREVENT:                 return handleEventUser(event.user);                 // SDL_UserEvent

            default:                            return handleEventUnknown(event.common);            // SDL_CommonEvent
        }
    }
}

void Application::handleEventQuit(SDL_QuitEvent const& /*event*/)
{
    exitLoop();
}

void Application::handleEventUnknown(SDL_CommonEvent const& event)
{
    std::cerr << "Unknown Event: " << event.type << "\n";
    throw std::runtime_error("Unknown Event");
}

void Application::drawWindows()
{
    for (auto& window: windows)
    {
        window.second->draw();
    }
}
