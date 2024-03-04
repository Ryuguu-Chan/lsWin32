#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif


#include <iostream> // std::cout << std::newline

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

	bool newline() {
		std::cout << std::endl;
	}
#endif
}