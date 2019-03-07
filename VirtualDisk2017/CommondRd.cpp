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
	bool s = false;
	for (auto it = allSubs.begin(); it != allSubs.end();)
	{
		if (*it == "\\s")
		{
			s = true;
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