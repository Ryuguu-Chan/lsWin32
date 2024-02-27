#include <iostream>

// RUNS ON C++17 !!!
#include <filesystem>

#include "Compute.h"
#include "appStrings.h"


namespace filesystem = std::filesystem;

int main(int argc, char** argv) {

	filesystem::path currentWorkingDirectory;

	if (argc == 1) {
		currentWorkingDirectory = filesystem::current_path();
	}
	else {
		// TODO: prendre en compte les options
		if (filesystem::exists(argv[1])) {
			if (filesystem::is_directory(argv[1])) {
				currentWorkingDirectory = argv[1];
			}
			else {
				std::cout << appStrings::NOT_A_DIRECTORY_ERROR_STR << std::endl;
				return EXIT_FAILURE;
			}
		}
		else {
			std::cout << appStrings::DOES_NOT_EXIST_ERROR_STR << std::endl;
			return EXIT_FAILURE;
		}
	}

	for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
		std::cout << dir_entry.path().filename().generic_string() << std::endl;
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}