#include "DebugApplication.h"

using namespace ThorsAnvil::UI;

void DebugApplication::handleEventQuit(SDL_QuitEvent const& event)
{
    std::cerr << "handleEventQuit\n";
    Application::handleEventQuit(event);
}

void DebugApplication::handleEventTerminating(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventTerminating\n";
}

void DebugApplication::handleEventLowMemory(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventLowMemory\n";
}

void DebugApplication::handleEventBackground(SDL_CommonEvent const& /*event*/, bool /*done*/)
{
    std::cerr << "handleEventBackground\n";
}

void DebugApplication::handleEventForeground(SDL_CommonEvent const& /*event*/, bool /*done*/)
{
    std::cerr << "handleEventForeground\n";
}

void DebugApplication::handleEventLocalUpdate(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventLocalUpdate\n";
}


/* Display events           0x015*  */
void DebugApplication::handleEventDisplayEvent(SDL_DisplayEvent const& /*event*/)
{
    std::cerr << "handleEventDisplayEvent\n";
}


/* Window events            0x020*  */
void DebugApplication::handleEventWindowShow(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowShow\n";
}

void DebugApplication::handleEventWindowHide(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowHide\n";
}

void DebugApplication::handleEventWindowExpose(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowExpose\n";
}

void DebugApplication::handleEventWindowMmoved(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowMmoved\n";
}

void DebugApplication::handleEventWindowResized(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowResized\n";
}

void DebugApplication::handleEventWindowSizeChange(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowSizeChange\n";
}

void DebugApplication::handleEventWindowMin(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowMin\n";
}

void DebugApplication::handleEventWindowMax(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowMax\n";
}

void DebugApplication::handleEventWindowRestore(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowRestore\n";
}

void DebugApplication::handleEventWindowEnter(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowEnter\n";
}

void DebugApplication::handleEventWindowLeave(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowLeave\n";
}

void DebugApplication::handleEventWindowFocusGain(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowFocusGain\n";
}

void DebugApplication::handleEventWindowFocusLost(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowFocusLost\n";
}

void DebugApplication::handleEventWindowClose(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowClose\n";
}

void DebugApplication::handleEventWindowTakeFocus(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowTakeFocus\n";
}

void DebugApplication::handleEventWindowHitTest(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowHitTest\n";
}

void DebugApplication::handleEventWindowICCProfChange(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowICCProfChange\n";
}

void DebugApplication::handleEventWindowDisplayChange(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowDisplayChange\n";
}

void DebugApplication::handleEventWindowUnknown(SDL_WindowEvent const& /*event*/)
{
    std::cerr << "handleEventWindowUnknown\n";
}

void DebugApplication::handleEventSystemEvent(SDL_SysWMEvent const& /*event*/)
{
    std::cerr << "handleEventSystemEvent\n";
}


/* Keyboard events          0x030*  */
void DebugApplication::handleEventKeyDown(SDL_KeyboardEvent const& /*event*/)
{
    std::cerr << "handleEventKeyDown\n";
}

void DebugApplication::handleEventKeyUp(SDL_KeyboardEvent const& /*event*/)
{
    std::cerr << "handleEventKeyUp\n";
}

void DebugApplication::handleEventTextEditting(SDL_TextEditingEvent const& /*event*/)
{
    std::cerr << "handleEventTextEditting\n";
}

void DebugApplication::handleEventTextInput(SDL_TextInputEvent const& /*event*/)
{
    std::cerr << "handleEventTextInput\n";
}

void DebugApplication::handleEventTextEditingExt(SDL_TextEditingExtEvent const& /*event*/)
{
    std::cerr << "handleEventTextEditingExt\n";
}

void DebugApplication::handleEventKeyMapChanged(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventKeyMapChanged\n";
}


/* Mouse events             0x040*  */
void DebugApplication::handleEventMouseMove(SDL_MouseMotionEvent const& /*event*/)
{
    static long long count = 0;
    ++count;
    if (count % 100 == 0)
    {
        std::cerr << "handleEventMouseMove\n";
    }
}

void DebugApplication::handleEventMouseDown(SDL_MouseButtonEvent const& /*event*/)
{
    std::cerr << "handleEventMouseDown\n";
}

void DebugApplication::handleEventMouseUp(SDL_MouseButtonEvent const& /*event*/)
{
    std::cerr << "handleEventMouseUp\n";
}

void DebugApplication::handleEventMouseWheel(SDL_MouseWheelEvent const& /*event*/)
{
    std::cerr << "handleEventMouseWheel\n";
}


/* Joystick events          0x060*  */
void DebugApplication::handleEventJoyMotion(SDL_JoyAxisEvent const& /*event*/)
{
    std::cerr << "handleEventJoyMotion\n";
}

void DebugApplication::handleEventJoyBall(SDL_JoyBallEvent const& /*event*/)
{
    std::cerr << "handleEventJoyBall\n";
}

void DebugApplication::handleEventJoyHat(SDL_JoyHatEvent const& /*event*/)
{
    std::cerr << "handleEventJoyHat\n";
}

void DebugApplication::handleEventJoyButtonDown(SDL_JoyButtonEvent const& /*event*/)
{
    std::cerr << "handleEventJoyButtonDown\n";
}

void DebugApplication::handleEventJoyButtonUp(SDL_JoyButtonEvent const& /*event*/)
{
    std::cerr << "handleEventJoyButtonUp\n";
}

void DebugApplication::handleEventJoyDeviceAdd(SDL_JoyDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventJoyDeviceAdd\n";
}

void DebugApplication::handleEventJoyDeviceRem(SDL_JoyDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventJoyDeviceRem\n";
}

void DebugApplication::handleEventJoyBattery(SDL_JoyBatteryEvent const& /*event*/)
{
    std::cerr << "handleEventJoyBattery\n";
}


/* Game controller events   0x065*  */
void DebugApplication::handleEventControlMotion(SDL_ControllerAxisEvent const& /*event*/)
{
    std::cerr << "handleEventControlMotion\n";
}

void DebugApplication::handleEventControlButtonDown(SDL_ControllerButtonEvent const& /*event*/)
{
    std::cerr << "handleEventControlButtonDown\n";
}

void DebugApplication::handleEventControlButtonUp(SDL_ControllerButtonEvent const& /*event*/)
{
    std::cerr << "handleEventControlButtonUp\n";
}

void DebugApplication::handleEventControlDeviceAdd(SDL_ControllerDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventControlDeviceAdd\n";
}

void DebugApplication::handleEventControlDeviceRem(SDL_ControllerDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventControlDeviceRem\n";
}

void DebugApplication::handleEventControlDeviceMap(SDL_ControllerDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventControlDeviceMap\n";
}


void DebugApplication::handleEventTouchPadDown(SDL_ControllerTouchpadEvent const& /*event*/)
{
    std::cerr << "handleEventTouchPadDown\n";
}

void DebugApplication::handleEventTouchPadUp(SDL_ControllerTouchpadEvent const& /*event*/)
{
    std::cerr << "handleEventTouchPadUp\n";
}

void DebugApplication::handleEventTouchPadMotion(SDL_ControllerTouchpadEvent const& /*event*/)
{
    std::cerr << "handleEventTouchPadMotion\n";
}

void DebugApplication::handleEventTouchPadSendor(SDL_ControllerSensorEvent const& /*event*/)
{
    std::cerr << "handleEventTouchPadSendor\n";
}


/* Touch events             0x070*  */
void DebugApplication::handleEventFingerDown(SDL_TouchFingerEvent const& /*event*/)
{
    std::cerr << "handleEventFingerDown\n";
}

void DebugApplication::handleEventFingerUp(SDL_TouchFingerEvent const& /*event*/)
{
    std::cerr << "handleEventFingerUp\n";
}

void DebugApplication::handleEventFingerMotion(SDL_TouchFingerEvent const& /*event*/)
{
    std::cerr << "handleEventFingerMotion\n";
}


/* Gesture events           0x080*  */
void DebugApplication::handleEventDollarGesture(SDL_DollarGestureEvent const& /*event*/)
{
    std::cerr << "handleEventDollarGesture\n";
}

void DebugApplication::handleEventDollarRecord(SDL_DollarGestureEvent const& /*event*/)
{
    std::cerr << "handleEventDollarRecord\n";
}

void DebugApplication::handleEventMultiGesture(SDL_MultiGestureEvent const& /*event*/)
{
    std::cerr << "handleEventMultiGesture\n";
}


/* Clipboard events         0x09*   */
void DebugApplication::handleEventClipboardUpdate(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventClipboardUpdate\n";
}


/* Drag and drop events     0x100*  */
void DebugApplication::handleEventDropFile(SDL_DropEvent const& /*event*/)
{
    std::cerr << "handleEventDropFile\n";
}

void DebugApplication::handleEventDropText(SDL_DropEvent const& /*event*/)
{
    std::cerr << "handleEventDropText\n";
}

void DebugApplication::handleEventDropBegin(SDL_DropEvent const& /*event*/)
{
    std::cerr << "handleEventDropBegin\n";
}

void DebugApplication::handleEventDropEnd(SDL_DropEvent const& /*event*/)
{
    std::cerr << "handleEventDropEnd\n";
}


/* Audio hotplug events     0x110*  */
void DebugApplication::handleEventAudioDeviceAdd(SDL_AudioDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventAudioDeviceAdd\n";
}

void DebugApplication::handleEventAudioDeviceRem(SDL_AudioDeviceEvent const& /*event*/)
{
    std::cerr << "handleEventAudioDeviceRem\n";
}


/* Sensor events            0x120*  */
void DebugApplication::handleEventSensorUpdate(SDL_SensorEvent const& /*event*/)
{
    std::cerr << "handleEventSensorUpdate\n";
}


/* Render events            0x200*  */
void DebugApplication::handleEventRenderTargetReset(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventRenderTargetReset\n";
}

void DebugApplication::handleEventRenderDeviceReset(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventRenderDeviceReset\n";
}


/* Internal events          0x7F0*  */
void DebugApplication::handleEventPollSentinel(SDL_CommonEvent const& /*event*/)
{
    std::cerr << "handleEventPollSentinel\n";
}


/* User events              0x800*  */
void DebugApplication::handleEventUser(SDL_UserEvent const& /*event*/)
{
    std::cerr << "handleEventUser\n";
}


void DebugApplication::handleEventUnknown(SDL_CommonEvent const& event)
{
    std::cerr << "handleEventUnknown\n";
    Application::handleEventUnknown(event);
}
