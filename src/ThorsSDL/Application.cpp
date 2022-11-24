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
    initialized = false;
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

void Application::eventLoop(std::function<void()>&& action, std::function<void(int)>&& eventDone)
{
    userEventDone   = std::move(eventDone);
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
    windows[window.getId()] = &window;
}

void Application::unregisterWindow(Window& window)
{
    windows.erase(windows.find(window.getId()));
}

WindowEventHandler& Application::getWindowHander(Uint32 windowId)
{
    auto find = windows.find(windowId);
    if (find != windows.end())
    {
        return *find->second;
    }

    static WindowEventHandler defaultWindowHandler;
    return defaultWindowHandler;
}

void Application::handleEvents()
{
    int count = 0;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ++count;
        switch (event.type)
        {
    /* Application events       0x010*  */
            case SDL_QUIT:                      handleEventQuit(event.quit);                    break;  // SDL_QuitEvent
            case SDL_APP_TERMINATING:           handleEventTerminating(event.common);           break;  // SDL_CommonEvent
            case SDL_APP_LOWMEMORY:             handleEventLowMemory(event.common);             break;  // SDL_CommonEvent
            case SDL_APP_WILLENTERBACKGROUND:   handleEventBackground(event.common, false);     break;  // SDL_CommonEvent
            case SDL_APP_DIDENTERBACKGROUND:    handleEventBackground(event.common, true);      break;  // SDL_CommonEvent
            case SDL_APP_WILLENTERFOREGROUND:   handleEventForeground(event.common, false);     break;  // SDL_CommonEvent
            case SDL_APP_DIDENTERFOREGROUND:    handleEventForeground(event.common, true);      break;  // SDL_CommonEvent
            case SDL_LOCALECHANGED:             handleEventLocalUpdate(event.common);           break;  // SDL_CommonEvent

    /* Display events           0x015*  */
            case SDL_DISPLAYEVENT:              handleEventDisplayEvent(event.display);         break;  // SDL_DisplayEvent

    /* Window events            0x020*  */
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_SHOWN:             handleEventWindowShow(event.window);            break;  // SDL_WindowEventzz
                    case SDL_WINDOWEVENT_HIDDEN:            handleEventWindowHide(event.window);            break;  // SDL_WindowEventz
                    case SDL_WINDOWEVENT_EXPOSED:           handleEventWindowExpose(event.window);          break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MOVED:             handleEventWindowMoved(event.window);           break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_RESIZED:           handleEventWindowResized(event.window);         break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_SIZE_CHANGED:      handleEventWindowSizeChange(event.window);      break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MINIMIZED:         handleEventWindowMin(event.window);             break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_MAXIMIZED:         handleEventWindowMax(event.window);             break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_RESTORED:          handleEventWindowRestore(event.window);         break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_ENTER:             handleEventWindowEnter(event.window);           break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_LEAVE:             handleEventWindowLeave(event.window);           break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_FOCUS_GAINED:      handleEventWindowFocusGain(event.window);       break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_FOCUS_LOST:        handleEventWindowFocusLost(event.window);       break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_CLOSE:             handleEventWindowClose(event.window);           break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_TAKE_FOCUS:        handleEventWindowTakeFocus(event.window);       break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_HIT_TEST:          handleEventWindowHitTest(event.window);         break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_ICCPROF_CHANGED:   handleEventWindowICCProfChange(event.window);   break;  // SDL_WindowEvent
                    case SDL_WINDOWEVENT_DISPLAY_CHANGED:   handleEventWindowDisplayChange(event.window);   break;  // SDL_WindowEvent
                    default:    handleEventWindowUnknown(event.window);                                     break;  // SDL_WindowEvent
                }
                break;
            }
            case SDL_SYSWMEVENT:                handleEventSystemEvent(event.syswm);            break;  // SDL_SysWMEvent

    /* Keyboard events          0x030*  */
            case SDL_KEYDOWN:                   handleEventKeyDown(event.key);                  break;  // SDL_KeyboardEvent
            case SDL_KEYUP:                     handleEventKeyUp(event.key);                    break;  // SDL_KeyboardEvent
            case SDL_TEXTEDITING:               handleEventTextEditting(event.edit);            break;  // SDL_TextEditingEvent
            case SDL_TEXTINPUT:                 handleEventTextInput(event.text);               break;  // SDL_TextInputEvent
            case SDL_KEYMAPCHANGED:             handleEventKeyMapChanged(event.common);         break;  // SDL_CommonEvent
            case SDL_TEXTEDITING_EXT:           handleEventTextEditingExt(event.editExt);       break;  // SDL_TextEditingExtEvent

    /* Mouse events             0x040*  */
            case SDL_MOUSEMOTION:               handleEventMouseMove(event.motion);             break;  // SDL_MouseMotionEvent
            case SDL_MOUSEBUTTONDOWN:           handleEventMouseDown(event.button);             break;  // SDL_MouseButtonEvent
            case SDL_MOUSEBUTTONUP:             handleEventMouseUp(event.button);               break;  // SDL_MouseButtonEvent
            case SDL_MOUSEWHEEL:                handleEventMouseWheel(event.wheel);             break;  // SDL_MouseWheelEvent

    /* Joystick events          0x060*  */
            case SDL_JOYAXISMOTION:             handleEventJoyMotion(event.jaxis);              break;  // SDL_JoyAxisEvent
            case SDL_JOYBALLMOTION:             handleEventJoyBall(event.jball);                break;  // SDL_JoyBallEvent
            case SDL_JOYHATMOTION:              handleEventJoyHat(event.jhat);                  break;  // SDL_JoyHatEvent
            case SDL_JOYBUTTONDOWN:             handleEventJoyButtonDown(event.jbutton);        break;  // SDL_JoyButtonEvent
            case SDL_JOYBUTTONUP:               handleEventJoyButtonUp(event.jbutton);          break;  // SDL_JoyButtonEvent
            case SDL_JOYDEVICEADDED:            handleEventJoyDeviceAdd(event.jdevice);         break;  // SDL_JoyDeviceEvent
            case SDL_JOYDEVICEREMOVED:          handleEventJoyDeviceRem(event.jdevice);         break;  // SDL_JoyDeviceEvent
            case SDL_JOYBATTERYUPDATED:         handleEventJoyBattery(event.jbattery);          break;  // SDL_JoyBatteryEvent

    /* Game controller events   0x065*  */
            case SDL_CONTROLLERAXISMOTION:      handleEventControlMotion(event.caxis);          break;  // SDL_ControllerAxisEvent
            case SDL_CONTROLLERBUTTONDOWN:      handleEventControlButtonDown(event.cbutton);    break;  // SDL_ControllerButtonEvent
            case SDL_CONTROLLERBUTTONUP:        handleEventControlButtonUp(event.cbutton);      break;  // SDL_ControllerButtonEvent
            case SDL_CONTROLLERDEVICEADDED:     handleEventControlDeviceAdd(event.cdevice);     break;  // SDL_ControllerDeviceEvent
            case SDL_CONTROLLERDEVICEREMOVED:   handleEventControlDeviceRem(event.cdevice);     break;  // SDL_ControllerDeviceEvent
            case SDL_CONTROLLERDEVICEREMAPPED:  handleEventControlDeviceMap(event.cdevice);     break;  // SDL_ControllerDeviceEvent

            case SDL_CONTROLLERTOUCHPADDOWN:    handleEventTouchPadDown(event.ctouchpad);       break;  // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERTOUCHPADUP:      handleEventTouchPadUp(event.ctouchpad);         break;  // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERTOUCHPADMOTION:  handleEventTouchPadMotion(event.ctouchpad);     break;  // SDL_ControllerTouchpadEvent
            case SDL_CONTROLLERSENSORUPDATE:    handleEventTouchPadSendor(event.csensor);       break;  // SDL_ControllerSensorEvent

    /* Touch events             0x070*  */
            case SDL_FINGERDOWN:                handleEventFingerDown(event.tfinger);           break;  // SDL_TouchFingerEvent
            case SDL_FINGERUP:                  handleEventFingerUp(event.tfinger);             break;  // SDL_TouchFingerEvent
            case SDL_FINGERMOTION:              handleEventFingerMotion(event.tfinger);         break;  // SDL_TouchFingerEvent

    /* Gesture events           0x080*  */
            case SDL_DOLLARGESTURE:             handleEventDollarGesture(event.dgesture);       break;  // SDL_DollarGestureEvent
            case SDL_DOLLARRECORD:              handleEventDollarRecord(event.dgesture);        break;  // SDL_DollarGestureEvent
            case SDL_MULTIGESTURE:              handleEventMultiGesture(event.mgesture);        break;  // SDL_MultiGestureEvent

    /* Clipboard events         0x09*   */
            case SDL_CLIPBOARDUPDATE:           handleEventClipboardUpdate(event.common);       break;  // SDL_CommonEvent

    /* Drag and drop events     0x100*  */
            case SDL_DROPFILE:                  handleEventDropFile(event.drop);                break;  // SDL_DropEvent
            case SDL_DROPTEXT:                  handleEventDropText(event.drop);                break;  // SDL_DropEvent
            case SDL_DROPBEGIN:                 handleEventDropBegin(event.drop);               break;  // SDL_DropEvent
            case SDL_DROPCOMPLETE:              handleEventDropEnd(event.drop);                 break;  // SDL_DropEvent

    /* Audio hotplug events     0x110*  */
            case SDL_AUDIODEVICEADDED:          handleEventAudioDeviceAdd(event.adevice);       break;  // SDL_AudioDeviceEvent
            case SDL_AUDIODEVICEREMOVED:        handleEventAudioDeviceRem(event.adevice);       break;  // SDL_AudioDeviceEvent

    /* Sensor events            0x120*  */
            case SDL_SENSORUPDATE:              handleEventSensorUpdate(event.sensor);          break;  // SDL_SensorEvent

    /* Render events            0x200*  */
            case SDL_RENDER_TARGETS_RESET:      handleEventRenderTargetReset(event.common);     break;  // SDL_CommonEvent
            case SDL_RENDER_DEVICE_RESET:       handleEventRenderDeviceReset(event.common);     break;  // SDL_CommonEvent

    /* Internal events          0x7F0*  */
            case SDL_POLLSENTINEL:              handleEventPollSentinel(event.common);          break;  // SDL_CommonEvent

    /* User events              0x800*  */
            case SDL_USEREVENT:                 handleEventUser(event.user);                    break;  // SDL_UserEvent

            default:                            handleEventUnknown(event.common);               break;  // SDL_CommonEvent
        }
    }
    handleEventDone(count);
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

/* Window events            0x020*  */
void Application::handleEventWindowShow(SDL_WindowEvent const& event)                        {getWindowHander(event.windowID).handleEventWindowShow(event);}
void Application::handleEventWindowHide(SDL_WindowEvent const& event)                        {getWindowHander(event.windowID).handleEventWindowHide(event);}
void Application::handleEventWindowExpose(SDL_WindowEvent const& event)                      {getWindowHander(event.windowID).handleEventWindowExpose(event);}
void Application::handleEventWindowMoved(SDL_WindowEvent const& event)                       {getWindowHander(event.windowID).handleEventWindowMoved(event);}
void Application::handleEventWindowResized(SDL_WindowEvent const& event)                     {getWindowHander(event.windowID).handleEventWindowResized(event);}
void Application::handleEventWindowSizeChange(SDL_WindowEvent const& event)                  {getWindowHander(event.windowID).handleEventWindowSizeChange(event);}
void Application::handleEventWindowMin(SDL_WindowEvent const& event)                         {getWindowHander(event.windowID).handleEventWindowMin(event);}
void Application::handleEventWindowMax(SDL_WindowEvent const& event)                         {getWindowHander(event.windowID).handleEventWindowMax(event);}
void Application::handleEventWindowRestore(SDL_WindowEvent const& event)                     {getWindowHander(event.windowID).handleEventWindowRestore(event);}
void Application::handleEventWindowEnter(SDL_WindowEvent const& event)                       {getWindowHander(event.windowID).handleEventWindowEnter(event);}
void Application::handleEventWindowLeave(SDL_WindowEvent const& event)                       {getWindowHander(event.windowID).handleEventWindowLeave(event);}
void Application::handleEventWindowFocusGain(SDL_WindowEvent const& event)                   {getWindowHander(event.windowID).handleEventWindowFocusGain(event);}
void Application::handleEventWindowFocusLost(SDL_WindowEvent const& event)                   {getWindowHander(event.windowID).handleEventWindowFocusLost(event);}
void Application::handleEventWindowClose(SDL_WindowEvent const& event)                       {getWindowHander(event.windowID).handleEventWindowClose(event);}
void Application::handleEventWindowTakeFocus(SDL_WindowEvent const& event)                   {getWindowHander(event.windowID).handleEventWindowTakeFocus(event);}
void Application::handleEventWindowHitTest(SDL_WindowEvent const& event)                     {getWindowHander(event.windowID).handleEventWindowHitTest(event);}
void Application::handleEventWindowICCProfChange(SDL_WindowEvent const& event)               {getWindowHander(event.windowID).handleEventWindowICCProfChange(event);}
void Application::handleEventWindowDisplayChange(SDL_WindowEvent const& event)               {getWindowHander(event.windowID).handleEventWindowDisplayChange(event);}
void Application::handleEventWindowUnknown(SDL_WindowEvent const& event)                     {getWindowHander(event.windowID).handleEventWindowUnknown(event);}

/* Keyboard events          0x030*  */
void Application::handleEventKeyDown(SDL_KeyboardEvent const& event)                         {getWindowHander(event.windowID).handleEventKeyDown(event);}
void Application::handleEventKeyUp(SDL_KeyboardEvent const& event)                           {getWindowHander(event.windowID).handleEventKeyUp(event);}
void Application::handleEventTextEditting(SDL_TextEditingEvent const& event)                 {getWindowHander(event.windowID).handleEventTextEditting(event);}
void Application::handleEventTextInput(SDL_TextInputEvent const& event)                      {getWindowHander(event.windowID).handleEventTextInput(event);}
void Application::handleEventTextEditingExt(SDL_TextEditingExtEvent const& event)            {getWindowHander(event.windowID).handleEventTextEditingExt(event);}

/* Mouse events             0x040*  */
void Application::handleEventMouseMove(SDL_MouseMotionEvent const& event)                    {getWindowHander(event.windowID).handleEventMouseMove(event);}
void Application::handleEventMouseDown(SDL_MouseButtonEvent const& event)                    {getWindowHander(event.windowID).handleEventMouseDown(event);}
void Application::handleEventMouseUp(SDL_MouseButtonEvent const& event)                      {getWindowHander(event.windowID).handleEventMouseUp(event);}
void Application::handleEventMouseWheel(SDL_MouseWheelEvent const& event)                    {getWindowHander(event.windowID).handleEventMouseWheel(event);}

void Application::handleEventDone(int eventCount)                                            {userEventDone(eventCount);}
