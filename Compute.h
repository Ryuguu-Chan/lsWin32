#pragma once

#include <iostream> // _MAX_PATH

#ifdef _WIN32
#include <Windows.h>
#endif

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

	bool strEquals(const char* str1, const char* str2) {

		if (strlen(str1) != strlen(str2)) {
			return false;
		}

		for (int i = 0; i < strlen(str1); i++) {
			if (str1[i] != str2[i]) {
				return false;
			}
		}

		return true;
	}

#ifdef _WIN32
	LPCWSTR constCharToLPCWSTR(const char* str) {

		LPCWSTR out = L"";

		for (int i = 0; i < strlen(str); i++) {
			out += str[i];
		}

		return out;
	}
#endif
}