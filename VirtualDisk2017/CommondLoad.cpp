#include "CommondLoad.h"
#include "VirtualDiskManagerObserver.h"
CommondLoad::CommondLoad(CommondEnum type)
	:Commond(type)
{
}

CommondLoad::~CommondLoad()
{
}
bool CommondLoad::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 1)
	{
		return false;
	}
	VirtualDiskManagerObserver::GetInstance()->Notify_Load(allSubs.back().c_str());
	return true;
}