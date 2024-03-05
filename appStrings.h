#pragma once

namespace appStrings {
	const char* NOT_A_DIRECTORY_ERROR_STR = "ls only works on directories!";
	const char* DOES_NOT_EXIST_ERROR_STR = "it doesn't exist!";
	const char* ERROR_CONSOLE_SET_CURSOR_POSITION_STR = "something went wrong while positionning the console's cursor";
	const char* ERROR_GETTING_FILE_AUTHOR_NAME_STR = "[COULD NOT GET THE AUTHOR'S NAME]";
	const char* ERROR_FILE_ACCESS_DENIED_STR = "[ACCESS DENIED]";
	const char* SYNTAX_HELP_STR = "ls\n\t-a : show all files\n\t--author show the file's author\n\t-d : show only the directories\n\t-Q : put all entries in quote marks\n\t-R: recursive\n\t-t: sort from the newest to the oldest one\n\t--help: shows help\n\t--version: shows the current app version";
	const char* APP_VERSION_STR = "Ryuguu Chan's LS v0.1.0";
}