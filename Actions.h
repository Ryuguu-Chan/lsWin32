#pragma once

namespace Actions {
	bool SHOW_ALL_DIRECTORIES(const char* str) {
		return strcmp(str, "-a") || strcmp(str, "--all");
	}
}