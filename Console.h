#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

// debug
#include <iostream>

namespace Console {

#ifdef _WIN32
	BOOL setCursorPosition(SHORT x, SHORT y) {

		COORD coordinates;
		coordinates.X = x;
		coordinates.Y = y;

		return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
	}

	COORD getCursorPosition() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		
		return csbi.dwCursorPosition;
	}
#endif
}