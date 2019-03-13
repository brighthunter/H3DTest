#include "CommondSaf.h"
#include "VirtualDiskManagerObserver.h"
CommondSaf::CommondSaf(const char* type)
	:Commond(type)
{
}

CommondSaf::~CommondSaf()
{
}
bool CommondSaf::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 1)
	{
		return false;
	}
	VirtualDiskManagerObserver::GetInstance()->Notify_Saf(allSubs.back().c_str());
	return true;
}