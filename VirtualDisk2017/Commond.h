#ifndef _Commond_H_
#define _Commond_H_
#include "CommondData.h"
#include <list>
#include <string>
class Commond
{
public:
	Commond(const char* type);
	virtual ~Commond()  = 0 {};
	virtual bool analyzeCommond(std::list<std::string> allSubs) = 0;
	virtual bool analyzeCommondType(std::list<std::string> allSubs);
private:
	std::string m_ctype;
};


#endif