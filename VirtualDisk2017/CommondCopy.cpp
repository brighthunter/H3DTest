#include "CommondCopy.h"
#include "VirtualDiskManagerObserver.h"
CommondCopy::CommondCopy(CommondEnum type)
	:Commond(type)
{
}

CommondCopy::~CommondCopy()
{
}
bool CommondCopy::analyzeCommond(std::list<std::string> allSubs)
{
	bool res = true;
	if (allSubs.size() != 2)
	{
		printf("Copy Input Wrong Format Path1 Path2\n");
		return false;
	}
	res &= VirtualDiskManagerObserver::GetInstance()->Notify_CopyPath(allSubs.back(), *allSubs.begin());

	return res;
}