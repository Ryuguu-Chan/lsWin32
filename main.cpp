#include <iostream>
#include <Windows.h> // WINAPI

int main(int argc, char** argv) {

	char cwdName[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, cwdName);

	if (argc == 1) {

	}
	else {

	}

	return EXIT_SUCCESS;
}