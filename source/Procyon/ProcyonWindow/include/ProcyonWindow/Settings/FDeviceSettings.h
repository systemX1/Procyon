#pragma once

#ifndef PRWINDOW_SETTINGS_FDEVICESETTINGS_H
#define PRWINDOW_SETTINGS_FDEVICESETTINGS_H

#include <cstdint>

namespace PrWindow::Settings {
    class FDeviceSettings {

    public:
        /**
        * specifies whether to create a debug OpenGL context, which may have additional error and
        * performance issue reporting functionality. If OpenGL ES is requested, this hint is ignored
        */
        bool isDebugProfile = false;

        /**
        * Specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality
        * deprecated in the requested version of OpenGL is removed. This must only be used if the requested OpenGL
        * version is 3.0 or above. If OpenGL ES is requested, this hint is ignored.
        */
        bool isForwardCompatibility = false;

        /**
        * Specify the client API major version that the created context must be compatible with. The exact
        * behavior of these hints depend on the requested client API
        */
        uint8_t contextMajorVersion = 3;

        /**
        * Specify the client API minor version that the created context must be compatible with. The exact
        * behavior of these hints depend on the requested client API
        */
        uint8_t contextMinorVersion = 3;

        /**
        * Defines the amount of samples to use (Requiered for multi-sampling)
        */
        uint8_t samples = 4;

    };
}

#endif
