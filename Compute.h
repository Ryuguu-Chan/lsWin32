#pragma once

#include <iostream> // _MAX_PATH

namespace Compute {
	const char* removePollutingDoubleBackslashe(const char* str) {
		char* out[_MAX_PATH] { 0 };

		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == '\\' && str[i + 1] == '\\') {
				out[i] = (char*)str[i];
				i += 1;
			}
			else {
				out[i] = (char*)str[i];
			}
		}

		return (const char*)out;
	}
}