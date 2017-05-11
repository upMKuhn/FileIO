#pragma once
#include "Platform.h"
#include <iostream>

namespace FileIO { namespace Common {
#define ARSIZE(x) sizeof(x[0]) * sizeof(x)

		inline std::string removeTrailingSlash(std::string str)
		{
			size_t end = str.find_last_of(FILEIO_SLASH);
			return end == str.size() - 1 && end != 0 ? str.substr(0, str.size() - 1) : str;
		}

		inline std::wstring removeTrailingSlash(std::wstring str)
		{
			size_t end = str.find_last_of(FILEIO_SLASH);
			return end == str.size() - 1 && end != 0 ? str.substr(0, str.size() - 1) : str;
		}


		inline void console_wait_for_key(void)
		{
			std::cout << "Press Any Key to continue ... \n";
			getchar();
		}

		inline std::string stringToLower(std::string& str) {
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			return str;
		}

		inline std::wstring stringToLower(std::wstring& str) {
			std::transform(str.begin(), str.end(), str.begin(), ::towlower);
			return str;
		}

} }
