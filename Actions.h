#pragma once

#include "Compute.h" // strEquals

namespace Actions {
	bool SHOW_ALL_DIRECTORIES(const char* str) {
		//return strcmp(str, "-a") || strcmp(str, "--all");
		return Compute::strEquals(str, "-a") || Compute::strEquals(str, "--all");
	}

	bool SHOW_ALL_FILE_AUTHOR(const char* str) {
		//return strcmp(str, "--author");
		return Compute::strEquals(str, "--author");
	}

	bool SHOW_ONLY_DIRECTORIES(const char* str) {
		return Compute::strEquals(str, "-d");
	}
}