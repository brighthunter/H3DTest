#include "CommondLod.h"
#include "VirtualDiskManagerObserver.h"
CommondLod::CommondLod(const char* type)
	:Commond(type)
{
}

CommondLod::~CommondLod()
{
}
bool CommondLod::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 1)
	{
		return false;
	}
 	VirtualDiskManagerObserver::GetInstance()->Notify_Lod(allSubs.back().c_str());
	return true;
}