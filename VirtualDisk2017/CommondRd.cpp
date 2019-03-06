#include "CommondRd.h"
#include "VirtualDiskManagerObserver.h"
CommondRd::CommondRd(CommondEnum type)
	:Commond(type)
{
}

CommondRd::~CommondRd()
{
}
bool CommondRd::analyzeCommond(std::vector<std::string> allSubs)
{
	bool s = false;
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		if (*it == "\\s")
		{
			s = true;
			it = allSubs.erase(it);
		}
	}
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		VirtualDiskManagerObserver::GetInstance()->Notify_DeletePath((*it).c_str(),s);

	}
	return true;
}