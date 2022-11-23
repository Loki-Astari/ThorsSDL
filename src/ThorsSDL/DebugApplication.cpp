#include "DebugApplication.h"

using namespace ThorsAnvil::UI;

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

void DebugApplication::handleEventBackground(SDL_CommonEvent const& event, bool done)
{
    std::cerr << "handleEventBackground\n";
    Application::handleEventBackground(event, done);
}

void DebugApplication::handleEventForeground(SDL_CommonEvent const& event, bool done)
{
    std::cerr << "handleEventForeground\n";
    Application::handleEventForeground(event, done);
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
    if (count % 100 == 0)
    {
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
