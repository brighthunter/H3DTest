#include "CommondMklink.h"
CommondMklink::CommondMklink(CommondEnum type)
	:Commond(type)
{
}

CommondMklink::~CommondMklink()
{
}
bool CommondMklink::analyzeCommond(std::list<std::string> allSubs)
{
	return false;
}