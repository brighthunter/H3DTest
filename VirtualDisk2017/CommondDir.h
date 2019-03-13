#ifndef _CommondDir_H_
#define _CommondDir_H_
#include "Commond.h"
class CommondDir :public Commond
{
public:
	CommondDir(const char* type);
	virtual ~CommondDir();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif