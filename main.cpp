#include <iostream>

// RUNS ON C++17 !!!
#include <filesystem>


namespace filesystem = std::filesystem;

int main(int argc, char** argv) {

	filesystem::path currentWorkingDirectory = filesystem::current_path();

	std::cout << currentWorkingDirectory << std::endl;

	return EXIT_SUCCESS;
}