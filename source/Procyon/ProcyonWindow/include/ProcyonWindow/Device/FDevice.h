#pragma once

#ifndef PRWINDOW_DEVICE_FDEVICE_H
#define PRWINDOW_DEVICE_FDEVICE_H

#include <string>
#include <cassert>
#include <unordered_map>
#include <GLFW/glfw3.h>

#include "ProcyonWindow/Cursor/FCursor.h"
#include "ProcyonWindow/Settings/FDeviceSettings.h"

namespace PrWindow::Device {

    /**
    * The Device represents the windowing context. It is necessary to create a device in order to create a window
    */
    class FDevice {
    public:
        FDevice(const FDevice& p_other)                = default;
        FDevice(FDevice&& p_other) noexcept            = default;
        FDevice& operator=(const FDevice& p_other)     = default;
        FDevice& operator=(FDevice&& p_other) noexcept = default;

        /**
        * Bind a listener to this event to receive device errors
        */
        //static OvTools::Eventing::Event<EDeviceError, std::string> ErrorEvent;

        /**
        * The constructor of the device will take care about GLFW initialization
        */
        explicit FDevice(const Settings::FDeviceSettings& p_deviceSettings);

        /**
        * The destructor of the device will take care about GLFW destruction
        */
        ~FDevice();

        /**
        * Return the size, in pixels, of the primary monity
        */
        [[nodiscard]] std::pair<int16_t, int16_t> GetMonitorSize() const;

        /**
        * Return an instance of GLFWcursor corresponding to the given shape
        * @param p_cursorShape
        */
        [[nodiscard]] GLFWcursor* GetCursorInstance(Cursor::ECursorShape p_cursorShape) const;

        /**
        * Return true if the vsync is currently enabled
        */
        [[nodiscard]] bool HasVsync() const;

        /**
        * Enable or disable the vsync
        * @note You must call this method after creating and defining a window as the current context
        * @param p_value (True to enable vsync)
        */
        void SetVsync(bool p_value);

        /**
        * Enable the inputs and events managments with created windows
        * @note Should be called every frames
        */
        void PollEvents() const;

        /**
        * Returns the elapsed time since the device startup
        */
        [[nodiscard]] float GetElapsedTime() const;

    private:
        void BindErrorCallback();
        void CreateCursors();
        void DestroyCursors();

    private:
        bool m_vsync = true;
        bool m_isAlive = false;
        std::unordered_map<Cursor::ECursorShape, GLFWcursor*> m_cursors;
    };

}

#endif
