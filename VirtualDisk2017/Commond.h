#ifndef _Commond_H_
#define _Commond_H_
#include "CommondData.h"
#include <list>
#include <string>
class Commond
{
public:
	Commond(CommondEnum type);
	virtual ~Commond()  = 0 {};
	virtual bool analyzeCommond(std::list<std::string> allSubs) = 0;
private:
	CommondEnum m_ctype;
};


#endif