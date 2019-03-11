#include "CommondMove.h"
CommondMove::CommondMove(CommondEnum type)
	:Commond(type)
{
}

CommondMove::~CommondMove()
{
}
bool CommondMove::analyzeCommond(std::list<std::string> allSubs)
{
	//VirtualDiskManagerObserver::GetInstance()->Notify_Mklink(allSubs.back().c_str(), (*allSubs.begin()).c_str());
	return true;
}