#include "CommondDel.h"
#include "VirtualDiskManagerObserver.h"
CommondDel::CommondDel(CommondEnum type)
	:Commond(type)
{
}
CommondDel::~CommondDel()
{

}
bool CommondDel::analyzeCommond(std::list<std::string> allSubs)
{
	int s = 0;
	for (auto it = allSubs.begin(); it != allSubs.end();)
	{
		if (*it == "\\s")
		{
			s = 1;
			it = allSubs.erase(it);
		}
		else
			it++;
	}
	for (auto it = allSubs.begin(); it != allSubs.end(); it++)
	{
		VirtualDiskManagerObserver::GetInstance()->Notify_DeleteVirtualFile((*it).c_str(), s);

	}
	return true;
}