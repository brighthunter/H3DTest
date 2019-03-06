#include "CommondMd.h"
#include "CommondMd.h"
#include <string>
#include "VirtualDiskManagerObserver.h"
CommondMd::CommondMd(CommondEnum type)
	:Commond(type)
{
}

CommondMd::~CommondMd()
{
}
bool CommondMd::analyzeCommond(std::vector<std::string> allSubs)
{
	bool res = true;
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		res &= VirtualDiskManagerObserver::GetInstance()->Notify_CreatePath((*it).c_str());
	}

	return res;
}