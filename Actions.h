#pragma once

#include "Compute.h" // strEquals

namespace Actions {
	bool SHOW_ALL_DIRECTORIES(const char* str) {
		return Compute::strEquals(str, "-a") || Compute::strEquals(str, "--all");
	}

	bool SHOW_ALL_FILE_AUTHOR(const char* str) {
		return Compute::strEquals(str, "--author");
	}

	bool SHOW_ONLY_DIRECTORIES(const char* str) {
		return Compute::strEquals(str, "-d") || Compute::strEquals(str, "--directory");
	}

	bool SHOW_ALL_FILE_WITH_QUOTES(const char* str) {
		return Compute::strEquals(str, "-Q") || Compute::strEquals(str, "--quote-name");
	}

	bool SHOW_ALL_FILES_RECURSIVE(const char* str) {
		return Compute::strEquals(str, "-R") || Compute::strEquals(str, "--recursive");
	}

	bool SHOW_ALL_FILES_AND_SORT_BY_NEWEST_FIRST(const char* str) {
		return Compute::strEquals(str, "-t");
	}
}