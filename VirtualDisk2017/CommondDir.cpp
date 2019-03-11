#include "CommondDir.h"
#include "VirtualDiskManagerObserver.h"
CommondDir::CommondDir(CommondEnum type)
	:Commond(type)
{
}

CommondDir::~CommondDir()
{
}
bool CommondDir::analyzeCommond(std::list<std::string> allSubs)
{
	int state = 0;
	for (auto it = allSubs.begin(); it != allSubs.end(); )
	{
		if (*it == "/s")
		{
			state |= 0x1;
			it = allSubs.erase(it);
			continue;
		}
		else if (*it == "/ad")
		{
			state |= 0x10;
			it = allSubs.erase(it);
			continue;
		}
		else
			++it;
	}
	if (allSubs.size() == 0)
	{
		VirtualDiskManagerObserver::GetInstance()->Notify_PrintDir("", state);
	}
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		VirtualDiskManagerObserver::GetInstance()->Notify_PrintDir((*it).c_str(), state);
	}
	
	return true;
}