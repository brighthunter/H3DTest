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
		bool b = analyzeCommond(allSubs);
		if (!b)
			printf("�﷨�����ȷ\n");
		return true;
	}
	return false;
}