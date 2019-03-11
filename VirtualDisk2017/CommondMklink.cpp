#include "CommondMklink.h"
#include "VirtualDiskManagerObserver.h"
CommondMklink::CommondMklink(CommondEnum type)
	:Commond(type)
{
}

CommondMklink::~CommondMklink()
{
}
bool CommondMklink::analyzeCommond(std::list<std::string> allSubs)
{
	if (allSubs.size() != 2)
		return false;
	VirtualDiskManagerObserver::GetInstance()->Notify_Mklink(allSubs.back().c_str(), (*allSubs.begin()).c_str());
	return true;
}