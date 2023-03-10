#pragma once

#ifndef PRWINDOW_SETTINGS_FWINDOWSETTINGS_H
#define PRWINDOW_SETTINGS_FWINDOWSETTINGS_H

#include <string>

#include "ProcyonWindow/Cursor/FCursor.h"

namespace PrWindow::Settings {

    class FWindowSettings {
    public:
		/**
		* A simple constant used to ignore a value setting (Let the program decide for you)
		* @note You can you WindowSettings::DontCare only where it is indicated
		*/
		constexpr static int32_t DO_NOT_CRAE = -1;

		/**
		* Title of the window (Displayed in the title bar)
		*/
		std::string title;

		/**
		* Width in pixels of the window
		*/
		uint16_t width;

		/**
		* Height in pixels of the window
		*/
		uint16_t height;

		/**
		* Minimum width of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t minimumWidth = DO_NOT_CRAE;

		/**
		* Minimum height of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t minimumHeight = DO_NOT_CRAE;

		/**
		* Maximum width of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t maximumWidth = DO_NOT_CRAE;

		/**
		* Maximum height of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t maximumHeight = DO_NOT_CRAE;

		/**
		* Specifies if the window is by default in isFullscreen or windowed mode
		*/
		bool isFullscreen = false;

		/**
		* Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc.
		* An undecorated window may still allow the user to generate close events on some platforms. This hint is ignored
		* for full screen windows.
		*/
		bool isDecorated = true;

		/**
		* specifies whether the windowed mode window will be isResizable by the user. The window will still be isResizable using
		* the "SetSize(uint16_t, uint16_t)" method of the "Window" class. This hint is ignored for full screen windows
		*/
		bool isResizable = true;

		/**
		* Specifies whether the windowed mode window will be given input focus when created. This hint is ignored for
		* full screen and initially hidden windows.
		*/
		bool isFocused = true;

		/**
		* Specifies whether the windowed mode window will be isMaximized when created. This hint is ignored for full screen windows.
		*/
		bool isMaximized = false;

		/**
		* Specifies whether the windowed mode window will be isFloating above other regular windows, also called topmost or always-on-top.
		* This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This hint is
		* ignored for full screen windows.
		*/
		bool isFloating = false;

		/**
		* Specifies whether the windowed mode window will be initially isVisible. This hint is ignored for full screen windows.
		*/
		bool isVisible = true;

		/**
		* Specifies whether the full screen window will automatically iconify and restore
		* the previous video mode on input focus loss. This hint is ignored for windowed mode windows
		*/
		bool isAutoIconify = true;

		/**
		* Specifies the desired refresh rate for full screen windows. If set to WindowSettings::DontCare, the highest
		* available refresh rate will be used. This hint is ignored for windowed mode windows.
		*/
		int32_t refreshRate = DO_NOT_CRAE;

		/**
		* Specifies the default cursor mode of the window
		*/
		Cursor::ECursorMode cursorMode = Cursor::ECursorMode::Normal;

		/**
		* Specifies the default cursor shape of the window
		*/
		Cursor::ECursorShape cursorShape = Cursor::ECursorShape::Arrow;

		/**
		* Defines the number of samples to use (For anti-aliasing)
		*/
		int32_t samples = 4;
    };


}

#endif