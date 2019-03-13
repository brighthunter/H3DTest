#include "CommondMove.h"
#include "VirtualDiskManagerObserver.h"
CommondMove::CommondMove(const char* type)
	:Commond(type)
{
}

CommondMove::~CommondMove()
{
}
bool CommondMove::analyzeCommond(std::list<std::string> allSubs)
{
	int state = 0;
	for (auto it = allSubs.begin(); it != allSubs.end(); )
	{
		if (*it == "/s")
		{
			state |= 0x1;
			it = allSubs.erase(it);
			continue;
		}
		else
			++it;
	}
	VirtualDiskManagerObserver::GetInstance()->Notify_Move(allSubs.back().c_str(), (*allSubs.begin()).c_str(),state);
	return true;
}