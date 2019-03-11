#include "CommondSave.h"
#include "VirtualDiskManagerObserver.h"
CommondSave::CommondSave(CommondEnum type)
	:Commond(type)
{
}

CommondSave::~CommondSave()
{
}
bool CommondSave::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 1)
	{
		return false;
	}
	VirtualDiskManagerObserver::GetInstance()->Notify_Save(allSubs.back().c_str());
	return true;
}