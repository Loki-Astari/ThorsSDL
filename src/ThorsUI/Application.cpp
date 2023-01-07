#include "Application.h"
#include "Window.h"
#include <stdexcept>
#include <chrono>


using namespace ThorsAnvil::UI;

Application* Application::initialized = nullptr;

bool KeyboardState::isPressed(SDL_Scancode keyCode) const
{
    static int   numkeys;
    static const Uint8*     state = SDL_GetKeyboardState(&numkeys);

    return state[keyCode] == 1;
}

KeyboardState const& Hardware::getKeyboardState() const
{
    static KeyboardState    keyboardState;
    return keyboardState;
}

Application::Application(InitValue init, InitLibs libs)
    : finished(false)
{
    if (initialized) {
        throw std::runtime_error("Attempt to re-initialize SDL");
    }
    sdl2 = std::make_unique<SDL::Lib_Main>(init);

    initSubSystem(libs);

    initialized = this;
}

Application::Application(InitLibs libs)
    : Application(Everything, libs)
{}

Application& Application::getInstance()
{
    if (initialized == nullptr) {
        throw std::runtime_error("No Application Exists");
    }
    return *initialized;
}

Application::~Application() noexcept(false)
{
    if (windows.size() != 0) {
        throw std::runtime_error("Killing Application with active windows");
    }
    initialized = nullptr;
}

void Application::initSubSystem(InitValue init)
{
    auto result = SDL_InitSubSystem(static_cast<Uint32>(init));
    if (result != 0) {
        throw std::runtime_error("Failed to init sub system");
    }
}

void Application::quitSubSystem(InitValue init)
{
    SDL_QuitSubSystem(static_cast<Uint32>(init));
}

void Application::enableTextInput(bool enable)
{
    static int usingCount = 0;
    if (enable)
    {
        if (usingCount == 0) {
            SDL_StartTextInput();
        }
        ++usingCount;
    }
    else
    {
        --usingCount;
        if (usingCount == 0) {
            SDL_StopTextInput();
        }
    }
}

void Application::initSubSystem(InitLibs init)
{
    if (init & Fonts) {
        sdl2ttf = std::make_unique<SDL::Lib_TTF>();
    }
    if (init & Images) {
        sdl2image = std::make_unique<SDL::Lib_Image>(init);
    }
}

void Application::quitSubSystem(InitLibs init)
{
    if (init & Fonts) {
        sdl2ttf.reset();
    }
    if (init & Images) {
        sdl2image.reset();
    }
}

void Application::eventLoop(int fps, std::function<void(int)>&& eventDone)
{
    static std::chrono::time_point<std::chrono::system_clock> lastUpdate{};
    const int millisondsToWaitPerDrawCycle = 1000 / fps;
    userEventDone   = std::move(eventDone);

    try
    {
        while (!finished)
        {
            int eventCount = handleEvents();

            updateState(eventCount);

            std::chrono::time_point thisTime = std::chrono::system_clock::now();
            std::chrono::milliseconds   diff = std::chrono::duration_cast<std::chrono::milliseconds>(thisTime - lastUpdate);

            if (diff.count() >= millisondsToWaitPerDrawCycle)
            {
                lastUpdate = thisTime;
                drawWindows();
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        std::cerr << "SDL Error: " << SDL_GetError() << "\n";
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
    if (find != windows.end()) {
        return *find->second;
    }

    static WindowEventHandler defaultWindowHandler;
    return defaultWindowHandler;
}

void Application::updateState(int eventCount)
{
    userEventDone(eventCount);

    for (auto& window: windows) {
        window.second->updateState();
    }
}

void Application::drawWindows()
{
    for (auto& window: windows) {
        window.second->draw();
    }
}

int Application::handleEvents()
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
            case SDL_APP_WILLENTERBACKGROUND:   handleEventBackgroundEnterAboutTo(event.common);break;  // SDL_CommonEvent
            case SDL_APP_DIDENTERBACKGROUND:    handleEventBackgroundEnterDone(event.common);   break;  // SDL_CommonEvent
            case SDL_APP_WILLENTERFOREGROUND:   handleEventForegroundEnterAboutTo(event.common);break;  // SDL_CommonEvent
            case SDL_APP_DIDENTERFOREGROUND:    handleEventForegroundEnterDone(event.common);   break;  // SDL_CommonEvent
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
    return count;
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


void DebugApplication::handleEventQuit(SDL_QuitEvent const& event)
{
    std::cerr << "handleEventQuit\n";
    Application::handleEventQuit(event);
}

void DebugApplication::handleEventTerminating(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventTerminating\n";
    Application::handleEventTerminating(event);
}

void DebugApplication::handleEventLowMemory(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventLowMemory\n";
    Application::handleEventLowMemory(event);
}

void DebugApplication::handleEventBackgroundEnterAboutTo(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventBackgroundEnterAboutTo\n";
    Application::handleEventBackgroundEnterAboutTo(event);
}

void DebugApplication::handleEventBackgroundEnterDone(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventBackgroundEnterDone\n";
    Application::handleEventBackgroundEnterDone(event);
}

void DebugApplication::handleEventForegroundEnterAboutTo(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventForegroundEnterAboutTo\n";
    Application::handleEventForegroundEnterAboutTo(event);
}

void DebugApplication::handleEventForegroundEnterDone(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventForegroundEnterDone\n";
    Application::handleEventForegroundEnterDone(event);
}

void DebugApplication::handleEventLocalUpdate(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventLocalUpdate\n";
    Application::handleEventLocalUpdate(event);
}


/* Display events           0x015*  */
void DebugApplication::handleEventDisplayEvent(SDL_DisplayEvent const& event)
{
    std::cerr << "handleEventDisplayEvent\n";
    Application::handleEventDisplayEvent(event);
}


/* Window events            0x020*  */
void DebugApplication::handleEventWindowShow(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowShow\n";
    Application::handleEventWindowShow(event);
}

void DebugApplication::handleEventWindowHide(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowHide\n";
    Application::handleEventWindowHide(event);
}

void DebugApplication::handleEventWindowExpose(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowExpose\n";
    Application::handleEventWindowExpose(event);
}

void DebugApplication::handleEventWindowMoved(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowMoved\n";
    Application::handleEventWindowMoved(event);
}

void DebugApplication::handleEventWindowResized(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowResized\n";
    Application::handleEventWindowResized(event);
}

void DebugApplication::handleEventWindowSizeChange(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowSizeChange\n";
    Application::handleEventWindowSizeChange(event);
}

void DebugApplication::handleEventWindowMin(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowMin\n";
    Application::handleEventWindowMin(event);
}

void DebugApplication::handleEventWindowMax(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowMax\n";
    Application::handleEventWindowMax(event);
}

void DebugApplication::handleEventWindowRestore(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowRestore\n";
    Application::handleEventWindowRestore(event);
}

void DebugApplication::handleEventWindowEnter(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowEnter\n";
    Application::handleEventWindowEnter(event);
}

void DebugApplication::handleEventWindowLeave(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowLeave\n";
    Application::handleEventWindowLeave(event);
}

void DebugApplication::handleEventWindowFocusGain(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowFocusGain\n";
    Application::handleEventWindowFocusGain(event);
}

void DebugApplication::handleEventWindowFocusLost(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowFocusLost\n";
    Application::handleEventWindowFocusLost(event);
}

void DebugApplication::handleEventWindowClose(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowClose\n";
    Application::handleEventWindowClose(event);
}

void DebugApplication::handleEventWindowTakeFocus(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowTakeFocus\n";
    Application::handleEventWindowTakeFocus(event);
}

void DebugApplication::handleEventWindowHitTest(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowHitTest\n";
    Application::handleEventWindowHitTest(event);
}

void DebugApplication::handleEventWindowICCProfChange(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowICCProfChange\n";
    Application::handleEventWindowICCProfChange(event);
}

void DebugApplication::handleEventWindowDisplayChange(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowDisplayChange\n";
    Application::handleEventWindowDisplayChange(event);
}

void DebugApplication::handleEventWindowUnknown(SDL_WindowEvent const& event)
{
    std::cerr << "handleEventWindowUnknown\n";
    Application::handleEventWindowUnknown(event);
}

void DebugApplication::handleEventSystemEvent(SDL_SysWMEvent const& event)
{
    std::cerr << "handleEventSystemEvent\n";
    Application::handleEventSystemEvent(event);
}


/* Keyboard events          0x030*  */
void DebugApplication::handleEventKeyDown(SDL_KeyboardEvent const& event)
{
    std::cerr << "handleEventKeyDown\n";
    Application::handleEventKeyDown(event);
}

void DebugApplication::handleEventKeyUp(SDL_KeyboardEvent const& event)
{
    std::cerr << "handleEventKeyUp\n";
    Application::handleEventKeyUp(event);
}

void DebugApplication::handleEventTextEditting(SDL_TextEditingEvent const& event)
{
    std::cerr << "handleEventTextEditting\n";
    Application::handleEventTextEditting(event);
}

void DebugApplication::handleEventTextInput(SDL_TextInputEvent const& event)
{
    std::cerr << "handleEventTextInput\n";
    Application::handleEventTextInput(event);
}

void DebugApplication::handleEventTextEditingExt(SDL_TextEditingExtEvent const& event)
{
    std::cerr << "handleEventTextEditingExt\n";
    Application::handleEventTextEditingExt(event);
}

void DebugApplication::handleEventKeyMapChanged(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventKeyMapChanged\n";
    Application::handleEventKeyMapChanged(event);
}


/* Mouse events             0x040*  */
void DebugApplication::handleEventMouseMove(SDL_MouseMotionEvent const& event)
{
    static long long count = 0;
    ++count;
    if (count % 100 == 0) {
        std::cerr << "handleEventMouseMove\n";
    }
    Application::handleEventMouseMove(event);
}

void DebugApplication::handleEventMouseDown(SDL_MouseButtonEvent const& event)
{
    std::cerr << "handleEventMouseDown\n";
    Application::handleEventMouseDown(event);
}

void DebugApplication::handleEventMouseUp(SDL_MouseButtonEvent const& event)
{
    std::cerr << "handleEventMouseUp\n";
    Application::handleEventMouseUp(event);
}

void DebugApplication::handleEventMouseWheel(SDL_MouseWheelEvent const& event)
{
    std::cerr << "handleEventMouseWheel\n";
    Application::handleEventMouseWheel(event);
}


/* Joystick events          0x060*  */
void DebugApplication::handleEventJoyMotion(SDL_JoyAxisEvent const& event)
{
    std::cerr << "handleEventJoyMotion\n";
    Application::handleEventJoyMotion(event);
}

void DebugApplication::handleEventJoyBall(SDL_JoyBallEvent const& event)
{
    std::cerr << "handleEventJoyBall\n";
    Application::handleEventJoyBall(event);
}

void DebugApplication::handleEventJoyHat(SDL_JoyHatEvent const& event)
{
    std::cerr << "handleEventJoyHat\n";
    Application::handleEventJoyHat(event);
}

void DebugApplication::handleEventJoyButtonDown(SDL_JoyButtonEvent const& event)
{
    std::cerr << "handleEventJoyButtonDown\n";
    Application::handleEventJoyButtonDown(event);
}

void DebugApplication::handleEventJoyButtonUp(SDL_JoyButtonEvent const& event)
{
    std::cerr << "handleEventJoyButtonUp\n";
    Application::handleEventJoyButtonUp(event);
}

void DebugApplication::handleEventJoyDeviceAdd(SDL_JoyDeviceEvent const& event)
{
    std::cerr << "handleEventJoyDeviceAdd\n";
    Application::handleEventJoyDeviceAdd(event);
}

void DebugApplication::handleEventJoyDeviceRem(SDL_JoyDeviceEvent const& event)
{
    std::cerr << "handleEventJoyDeviceRem\n";
    Application::handleEventJoyDeviceRem(event);
}

void DebugApplication::handleEventJoyBattery(SDL_JoyBatteryEvent const& event)
{
    std::cerr << "handleEventJoyBattery\n";
    Application::handleEventJoyBattery(event);
}


/* Game controller events   0x065*  */
void DebugApplication::handleEventControlMotion(SDL_ControllerAxisEvent const& event)
{
    std::cerr << "handleEventControlMotion\n";
    Application::handleEventControlMotion(event);
}

void DebugApplication::handleEventControlButtonDown(SDL_ControllerButtonEvent const& event)
{
    std::cerr << "handleEventControlButtonDown\n";
    Application::handleEventControlButtonDown(event);
}

void DebugApplication::handleEventControlButtonUp(SDL_ControllerButtonEvent const& event)
{
    std::cerr << "handleEventControlButtonUp\n";
    Application::handleEventControlButtonUp(event);
}

void DebugApplication::handleEventControlDeviceAdd(SDL_ControllerDeviceEvent const& event)
{
    std::cerr << "handleEventControlDeviceAdd\n";
    Application::handleEventControlDeviceAdd(event);
}

void DebugApplication::handleEventControlDeviceRem(SDL_ControllerDeviceEvent const& event)
{
    std::cerr << "handleEventControlDeviceRem\n";
    Application::handleEventControlDeviceRem(event);
}

void DebugApplication::handleEventControlDeviceMap(SDL_ControllerDeviceEvent const& event)
{
    std::cerr << "handleEventControlDeviceMap\n";
    Application::handleEventControlDeviceMap(event);
}


void DebugApplication::handleEventTouchPadDown(SDL_ControllerTouchpadEvent const& event)
{
    std::cerr << "handleEventTouchPadDown\n";
    Application::handleEventTouchPadDown(event);
}

void DebugApplication::handleEventTouchPadUp(SDL_ControllerTouchpadEvent const& event)
{
    std::cerr << "handleEventTouchPadUp\n";
    Application::handleEventTouchPadUp(event);
}

void DebugApplication::handleEventTouchPadMotion(SDL_ControllerTouchpadEvent const& event)
{
    std::cerr << "handleEventTouchPadMotion\n";
    Application::handleEventTouchPadMotion(event);
}

void DebugApplication::handleEventTouchPadSendor(SDL_ControllerSensorEvent const& event)
{
    std::cerr << "handleEventTouchPadSendor\n";
    Application::handleEventTouchPadSendor(event);
}


/* Touch events             0x070*  */
void DebugApplication::handleEventFingerDown(SDL_TouchFingerEvent const& event)
{
    std::cerr << "handleEventFingerDown\n";
    Application::handleEventFingerDown(event);
}

void DebugApplication::handleEventFingerUp(SDL_TouchFingerEvent const& event)
{
    std::cerr << "handleEventFingerUp\n";
    Application::handleEventFingerUp(event);
}

void DebugApplication::handleEventFingerMotion(SDL_TouchFingerEvent const& event)
{
    std::cerr << "handleEventFingerMotion\n";
    Application::handleEventFingerMotion(event);
}


/* Gesture events           0x080*  */
void DebugApplication::handleEventDollarGesture(SDL_DollarGestureEvent const& event)
{
    std::cerr << "handleEventDollarGesture\n";
    Application::handleEventDollarGesture(event);
}

void DebugApplication::handleEventDollarRecord(SDL_DollarGestureEvent const& event)
{
    std::cerr << "handleEventDollarRecord\n";
    Application::handleEventDollarRecord(event);
}

void DebugApplication::handleEventMultiGesture(SDL_MultiGestureEvent const& event)
{
    std::cerr << "handleEventMultiGesture\n";
    Application::handleEventMultiGesture(event);
}


/* Clipboard events         0x09*   */
void DebugApplication::handleEventClipboardUpdate(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventClipboardUpdate\n";
    Application::handleEventClipboardUpdate(event);
}


/* Drag and drop events     0x100*  */
void DebugApplication::handleEventDropFile(SDL_DropEvent const& event)
{
    std::cerr << "handleEventDropFile\n";
    Application::handleEventDropFile(event);
}

void DebugApplication::handleEventDropText(SDL_DropEvent const& event)
{
    std::cerr << "handleEventDropText\n";
    Application::handleEventDropText(event);
}

void DebugApplication::handleEventDropBegin(SDL_DropEvent const& event)
{
    std::cerr << "handleEventDropBegin\n";
    Application::handleEventDropBegin(event);
}

void DebugApplication::handleEventDropEnd(SDL_DropEvent const& event)
{
    std::cerr << "handleEventDropEnd\n";
    Application::handleEventDropEnd(event);
}


/* Audio hotplug events     0x110*  */
void DebugApplication::handleEventAudioDeviceAdd(SDL_AudioDeviceEvent const& event)
{
    std::cerr << "handleEventAudioDeviceAdd\n";
    Application::handleEventAudioDeviceAdd(event);
}

void DebugApplication::handleEventAudioDeviceRem(SDL_AudioDeviceEvent const& event)
{
    std::cerr << "handleEventAudioDeviceRem\n";
    Application::handleEventAudioDeviceRem(event);
}


/* Sensor events            0x120*  */
void DebugApplication::handleEventSensorUpdate(SDL_SensorEvent const& event)
{
    std::cerr << "handleEventSensorUpdate\n";
    Application::handleEventSensorUpdate(event);
}


/* Render events            0x200*  */
void DebugApplication::handleEventRenderTargetReset(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventRenderTargetReset\n";
    Application::handleEventRenderTargetReset(event);
}

void DebugApplication::handleEventRenderDeviceReset(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventRenderDeviceReset\n";
    Application::handleEventRenderDeviceReset(event);
}


/* Internal events          0x7F0*  */
void DebugApplication::handleEventPollSentinel(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventPollSentinel\n";
    Application::handleEventPollSentinel(event);
}


/* User events              0x800*  */
void DebugApplication::handleEventUser(SDL_UserEvent const& event)
{
    std::cerr << "handleEventUser\n";
    Application::handleEventUser(event);
}


void DebugApplication::handleEventUnknown(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventUnknown\n";
    Application::handleEventUnknown(event);
}
