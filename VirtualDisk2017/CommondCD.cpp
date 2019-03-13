#include "CommondCd.h"
#include "VirtualDiskManagerObserver.h"
CommondCD::CommondCD(const char* type)
	:Commond(type)
{
}

CommondCD::~CommondCD()
{
}
bool CommondCD::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 1)
		return false;
	VirtualDiskManagerObserver::GetInstance()->Notify_SetCursor(allSubs.back().c_str());
	return true;
}