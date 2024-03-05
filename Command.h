#ifndef __RYUGUUCHAN_COMMAND_CLASS__
#define __RYUGUUCHAN_COMMAND_CLASS__
class Command
{
private:
	void* actionPtr;
public:

	void run();

	Command(void* actionPtr);
	~Command();
};
#endif