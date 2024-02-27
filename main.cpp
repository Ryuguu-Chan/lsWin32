#include <iostream>

// RUNS ON C++17 !!!
#include <filesystem>


namespace filesystem = std::filesystem;

int main(int argc, char** argv) {

	filesystem::path currentWorkingDirectory = filesystem::current_path();

	// TODO: prendre en compte les arguments

	for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
		std::cout << dir_entry.path() << " ";
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}