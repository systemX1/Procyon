#pragma once

#ifndef PRWINDOW_CURSOR_FCURSOR_H
#define PRWINDOW_CURSOR_FCURSOR_H

#include <GLFW/glfw3.h>

namespace PrWindow::Cursor {

    enum class ECursorMode : int {
        Normal    = GLFW_CURSOR_NORMAL,
        Disabled  = GLFW_CURSOR_DISABLED,
        Hidden    = GLFW_CURSOR_HIDDEN,
    };

    enum class ECursorShape : int {
        Arrow     = GLFW_ARROW_CURSOR,
        IBeam     = GLFW_IBEAM_CURSOR,
        Corsshair = GLFW_CROSSHAIR_CURSOR,
        Hand      = GLFW_HAND_CURSOR,
        HResize   = GLFW_HRESIZE_CURSOR,
        VResize   = GLFW_VRESIZE_CURSOR
    };

}

#endif
