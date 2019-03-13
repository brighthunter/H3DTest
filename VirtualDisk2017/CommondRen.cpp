#include "CommondRen.h"
#include "VirtualDiskManagerObserver.h"
CommondRen::CommondRen(const char* type)
	:Commond(type)
{
}

CommondRen::~CommondRen()
{
}
bool CommondRen::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 2)
		return false;
	VirtualDiskManagerObserver::GetInstance()->Notify_Rename(allSubs.back().c_str(), (*allSubs.begin()).c_str());
	return true;
}