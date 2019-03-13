#include "Commond.h"
Commond::Commond(const char* type)
	:m_ctype(type)
{
}
bool Commond::analyzeCommondType(std::list<std::string> allSubs)
{
	if (allSubs.back() == m_ctype)
	{
		allSubs.pop_back();
		return 	analyzeCommond(allSubs);
	}
	return false;
}