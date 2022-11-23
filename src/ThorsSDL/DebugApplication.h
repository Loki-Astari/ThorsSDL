#ifndef THORSANVIL_UI_DEBUG_APPLICATION_H
#define THORSANVIL_UI_DEBUG_APPLICATION_H

#include "ThorsSDLConfig.h"
#include "Application.h"

namespace ThorsAnvil::UI
{

class DebugApplication: public Application
{
    public:
        using Application::Application;

    private:
        virtual void handleEventQuit(SDL_QuitEvent const& /*event*/) override;
        virtual void handleEventTerminating(SDL_CommonEvent const& /*event*/) override;
        virtual void handleEventLowMemory(SDL_CommonEvent const& /*event*/) override;
        virtual void handleEventBackground(SDL_CommonEvent const& /*event*/, bool /*done*/) override;
        virtual void handleEventForeground(SDL_CommonEvent const& /*event*/, bool /*done*/) override;
        virtual void handleEventLocalUpdate(SDL_CommonEvent const& /*event*/) override;

    /* Display events           0x015*  */
        virtual void handleEventDisplayEvent(SDL_DisplayEvent const& /*event*/) override;

    /* Window events            0x020*  */
        virtual void handleEventWindowEvent(SDL_WindowEvent const& /*event*/) override;
        virtual void handleEventSystemEvent(SDL_SysWMEvent const& /*event*/) override;

    /* Keyboard events          0x030*  */
        virtual void handleEventKeyDown(SDL_KeyboardEvent const& /*event*/) override;
        virtual void handleEventKeyUp(SDL_KeyboardEvent const& /*event*/) override;
        virtual void handleEventTextEditting(SDL_TextEditingEvent const& /*event*/) override;
        virtual void handleEventTextInput(SDL_TextInputEvent const& /*event*/) override;
        virtual void handleEventTextEditingExt(SDL_TextEditingExtEvent const& /*event*/) override;
        virtual void handleEventKeyMapChanged(SDL_CommonEvent const& /*event*/) override;

    /* Mouse events             0x040*  */
        virtual void handleEventMouseMove(SDL_MouseMotionEvent const& /*event*/) override;
        virtual void handleEventMouseDown(SDL_MouseButtonEvent const& /*event*/) override;
        virtual void handleEventMouseUp(SDL_MouseButtonEvent const& /*event*/) override;
        virtual void handleEventMouseWheel(SDL_MouseWheelEvent const& /*event*/) override;

    /* Joystick events          0x060*  */
        virtual void handleEventJoyMotion(SDL_JoyAxisEvent const& /*event*/) override;
        virtual void handleEventJoyBall(SDL_JoyBallEvent const& /*event*/) override;
        virtual void handleEventJoyHat(SDL_JoyHatEvent const& /*event*/) override;
        virtual void handleEventJoyButtonDown(SDL_JoyButtonEvent const& /*event*/) override;
        virtual void handleEventJoyButtonUp(SDL_JoyButtonEvent const& /*event*/) override;
        virtual void handleEventJoyDeviceAdd(SDL_JoyDeviceEvent const& /*event*/) override;
        virtual void handleEventJoyDeviceRem(SDL_JoyDeviceEvent const& /*event*/) override;
        virtual void handleEventJoyBattery(SDL_JoyBatteryEvent const& /*event*/) override;

    /* Game controller events   0x065*  */
        virtual void handleEventControlMotion(SDL_ControllerAxisEvent const& /*event*/) override;
        virtual void handleEventControlButtonDown(SDL_ControllerButtonEvent const& /*event*/) override;
        virtual void handleEventControlButtonUp(SDL_ControllerButtonEvent const& /*event*/) override;
        virtual void handleEventControlDeviceAdd(SDL_ControllerDeviceEvent const& /*event*/) override;
        virtual void handleEventControlDeviceRem(SDL_ControllerDeviceEvent const& /*event*/) override;
        virtual void handleEventControlDeviceMap(SDL_ControllerDeviceEvent const& /*event*/) override;

        virtual void handleEventTouchPadDown(SDL_ControllerTouchpadEvent const& /*event*/) override;
        virtual void handleEventTouchPadUp(SDL_ControllerTouchpadEvent const& /*event*/) override;
        virtual void handleEventTouchPadMotion(SDL_ControllerTouchpadEvent const& /*event*/) override;
        virtual void handleEventTouchPadSendor(SDL_ControllerSensorEvent const& /*event*/) override;

    /* Touch events             0x070*  */
        virtual void handleEventFingerDown(SDL_TouchFingerEvent const& /*event*/) override;
        virtual void handleEventFingerUp(SDL_TouchFingerEvent const& /*event*/) override;
        virtual void handleEventFingerMotion(SDL_TouchFingerEvent const& /*event*/) override;

    /* Gesture events           0x080*  */
        virtual void handleEventDollarGesture(SDL_DollarGestureEvent const& /*event*/) override;
        virtual void handleEventDollarRecord(SDL_DollarGestureEvent const& /*event*/) override;
        virtual void handleEventMultiGesture(SDL_MultiGestureEvent const& /*event*/) override;

    /* Clipboard events         0x09*   */
        virtual void handleEventClipboardUpdate(SDL_CommonEvent const& /*event*/) override;

    /* Drag and drop events     0x100*  */
        virtual void handleEventDropFile(SDL_DropEvent const& /*event*/) override;
        virtual void handleEventDropText(SDL_DropEvent const& /*event*/) override;
        virtual void handleEventDropBegin(SDL_DropEvent const& /*event*/) override;
        virtual void handleEventDropEnd(SDL_DropEvent const& /*event*/) override;

    /* Audio hotplug events     0x110*  */
        virtual void handleEventAudioDeviceAdd(SDL_AudioDeviceEvent const& /*event*/) override;
        virtual void handleEventAudioDeviceRem(SDL_AudioDeviceEvent const& /*event*/) override;

    /* Sensor events            0x120*  */
        virtual void handleEventSensorUpdate(SDL_SensorEvent const& /*event*/) override;

    /* Render events            0x200*  */
        virtual void handleEventRenderTargetReset(SDL_CommonEvent const& /*event*/) override;
        virtual void handleEventRenderDeviceReset(SDL_CommonEvent const& /*event*/) override;

    /* Internal events          0x7F0*  */
        virtual void handleEventPollSentinel(SDL_CommonEvent const& /*event*/) override;

    /* User events              0x800*  */
        virtual void handleEventUser(SDL_UserEvent const& /*event*/) override;


        virtual void handleEventUnknown(SDL_CommonEvent const& /*event*/) override;
};

}

#endif