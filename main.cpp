#include <iostream>
#include <string> // std::string
#include <vector> // std::vector<T>
#include <chrono> // std::chrono

#include <Windows.h> // DWORD, LPTSTR, PSID, PSECURITY_DESCRIPTOR, CreateFile
#include <AclAPI.h>  // GetSecurityInfo

// RUNS ON C++17 !!!
// compiler used: Visual Studio C++ compiler
#include <filesystem> 

#include "Compute.h"
#include "appStrings.h"
#include "Actions.h"
#include "Console.h"

#pragma comment(lib, "advapi32.lib")

namespace filesystem = std::filesystem;

bool sortFunction(std::filesystem::directory_entry a, std::filesystem::directory_entry b) {
	std::chrono::duration a_time = a.last_write_time().time_since_epoch();
	std::chrono::duration b_time = b.last_write_time().time_since_epoch();

	return (a_time > b_time);
}

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
			
			if (Actions::SHOW_ALL_DIRECTORIES(argv[1])) {

				std::cout << "show everything!!" << std::endl;
				
				if (argc == 2) {
					currentWorkingDirectory = filesystem::current_path();
				}
				for (auto const& dir_entry : filesystem::directory_iterator { currentWorkingDirectory }) {

					if (dir_entry.path().filename().generic_string()[0] != '~' && dir_entry.path().filename().generic_string()[0] == '$') {
						std::cout << dir_entry.path().filename().generic_string() << std::endl;
					}
					std::cout << dir_entry.path().filename().generic_string() << std::endl;
				}

				return EXIT_SUCCESS;
			}
			else if (Actions::SHOW_ALL_FILE_AUTHOR(argv[1])) {

				currentWorkingDirectory = filesystem::current_path();
				
				for (auto const& dir_entry : filesystem::directory_iterator { currentWorkingDirectory }) {

					std::cout << dir_entry.path().filename().generic_string();

					if (!Console::setCursorPosition(40, Console::getCursorPosition().Y)) {
						return EXIT_FAILURE;
					}

					LPTSTR fileAuthor = NULL;
					LPTSTR domainName = NULL;
					DWORD dwFileAuthor = 1;
					DWORD dwDomainName = 1;
					DWORD dwReturnCode = 0;
					PSID pSidOwner = NULL;
					PSECURITY_DESCRIPTOR pSD = NULL;
					SID_NAME_USE eUse = SidTypeUnknown;
					BOOL bRtnBool = TRUE;

					LPCWSTR fileToLookUpTo = Compute::constCharToLPCWSTR(dir_entry.path().filename().generic_string().c_str());

					HANDLE hFile = CreateFile(
						fileToLookUpTo,
						GENERIC_READ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL
					);

					dwReturnCode = GetSecurityInfo(
						hFile,
						SE_FILE_OBJECT,
						OWNER_SECURITY_INFORMATION,
						&pSidOwner,
						NULL,
						NULL,
						NULL,
						&pSD
					);

					bRtnBool = LookupAccountSid(
						NULL,
						pSidOwner,
						fileAuthor,
						(LPDWORD)&dwFileAuthor,
						domainName,
						(LPDWORD)&dwDomainName,
						&eUse
					);

					// memory reallocation
					fileAuthor = (LPTSTR)GlobalAlloc(GMEM_FIXED, dwFileAuthor * sizeof(wchar_t));

					if (fileAuthor == NULL) {
						DWORD dwErrorCode = GetLastError();
						std::cout << "Something went wrong while reallocating the fileAuthor string: " << dwErrorCode << std::endl;
						return EXIT_FAILURE;
					}

					domainName = (LPTSTR)GlobalAlloc(GMEM_FIXED, dwDomainName * sizeof(wchar_t));

					// getting the file owner's name
					bRtnBool = LookupAccountSid(
						NULL,
						pSidOwner,
						fileAuthor,
						(LPDWORD)&dwFileAuthor,
						domainName,
						(LPDWORD)&dwDomainName,
						&eUse
					);

					if (bRtnBool == FALSE) {
						DWORD errorCode = 0;

						errorCode = GetLastError();
						if (errorCode == ERROR_NONE_MAPPED) {
							std::cout << "The file's author wasn't found" << std::endl;
						}
						else {
							std::cout << "Something went wrong while looking at the file's author " << std::endl;

						}

						return EXIT_FAILURE;
					}
					else if (bRtnBool == TRUE) {
						std::wcout << fileAuthor; 
					}
					Console::newline();
				}
			}
			else if (Actions::SHOW_ONLY_DIRECTORIES(argv[1])) {
				currentWorkingDirectory = filesystem::current_path();

				for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
					if (dir_entry.is_directory()) {
						std::cout << dir_entry.path().filename().generic_string() << std::endl;
					}
				}
			}
			else if (Actions::SHOW_ALL_FILE_WITH_QUOTES(argv[1])) {
				currentWorkingDirectory = filesystem::current_path();

				for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
					std::cout << "\"" << dir_entry.path().filename().generic_string() << "\"" << std::endl;
				}
			}
			else if (Actions::SHOW_ALL_FILES_RECURSIVE(argv[1])) {

				std::vector<filesystem::directory_entry> dirs;

				currentWorkingDirectory = filesystem::current_path();

				for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
					if (dir_entry.is_directory()) {
						dirs.push_back(dir_entry);
					}

					std::cout << dir_entry.path().filename().generic_string() << std::endl;
				}

				do
				{
					currentWorkingDirectory = dirs.at(0);

					for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
						
						if (dir_entry.is_directory()) {
							dirs.push_back(dir_entry);
						}

						std::cout << dir_entry.path().filename().generic_string() << std::endl;

					}

					// removing the actual dir
					dirs.erase(dirs.begin());

				} while (dirs.size() > 0);
			}
			else if (Actions::SHOW_ALL_FILES_AND_SORT_BY_NEWEST_FIRST(argv[1])) {

				std::vector<filesystem::directory_entry> files;

				// TODO: utiliser std::filesystem::directory_entry::last_write_time
				
				currentWorkingDirectory = filesystem::current_path();

				for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
					files.push_back(dir_entry);

					std::chrono::duration dateTime = dir_entry.last_write_time().time_since_epoch();

					// debug
					// std::cout << dateTime.count() << std::endl;
				}

				std::sort(files.begin(), files.end(), sortFunction);
				
				for (auto it = files.begin(); it != files.end(); it++) {
					std::cout << it->path().filename().generic_string() << std::endl;
				}

				files.clear();
			}
			else if (Actions::SHOW_HELP_TEXT(argv[1])) {
				std::cout << appStrings::SYNTAX_HELP_STR << std::endl;
				return EXIT_SUCCESS;
			}
			else if (Actions::SHOW_APP_VERSION(argv[1])) {
				std::cout << appStrings::APP_VERSION_STR << std::endl;
				return EXIT_SUCCESS;
			}
			else {
				std::cout << "error";
				return EXIT_FAILURE;
			}

			return EXIT_FAILURE;
		}
	}

	for (auto const& dir_entry : filesystem::directory_iterator{ currentWorkingDirectory }) {
		std::cout << dir_entry.path().filename().generic_string() << std::endl;
	}

	Console::newline();

	return EXIT_SUCCESS;
}