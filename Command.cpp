#include "Command.h"

Command::Command(void* actionPtr) {
	this->actionPtr = actionPtr;
}

Command::~Command()
{
	this->actionPtr = nullptr;
}

void Command::run() {
	actionPtr;
}