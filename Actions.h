#pragma once

namespace Actions {
	bool SHOW_ALL_DIRECTORIES(const char* str) {
		return str == "-a" || str == "--all";
	}
}