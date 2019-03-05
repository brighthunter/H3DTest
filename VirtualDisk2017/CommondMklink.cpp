#include "CommondMklink.h"
CommondMklink::CommondMklink(CommondEnum type)
	:Commond(type)
{
}

CommondMklink::~CommondMklink()
{
}
bool CommondMklink::analyzeCommond(std::vector<std::string> allSubs)
{
	return false;
}