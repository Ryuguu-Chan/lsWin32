#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Console {

#ifdef _WIN32
	bool setCursorPosition(SHORT x, SHORT y) {

		/*
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;

		HANDLE consoleOutputHandle = STD_OUTPUT_HANDLE;

		return SetConsoleCursorPosition(consoleOutputHandle, coordinates);
		*/

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		csbi.dwCursorPosition.X = x;
		csbi.dwCursorPosition.Y = y;
	}

	COORD getCursorPosition() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		return csbi.dwCursorPosition;
	}
#endif
}