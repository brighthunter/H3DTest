#include "CommondRd.h"
#include "VirtualDiskManagerObserver.h"
CommondRd::CommondRd(CommondEnum type)
	:Commond(type)
{
}

CommondRd::~CommondRd()
{
}
bool CommondRd::analyzeCommond(std::list<std::string> allSubs)
{
	int s = 0;
	for (auto it = allSubs.begin(); it != allSubs.end();)
	{
		if (*it == "\\s")
		{
			s = 1;
			it = allSubs.erase(it);
		}
		else
			it++;
	}
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		VirtualDiskManagerObserver::GetInstance()->Notify_DeletePath((*it).c_str(),s);

	}
	return true;
}