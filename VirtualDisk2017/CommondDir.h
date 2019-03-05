#ifndef _CommondDir_H_
#define _CommondDir_H_
#include "Commond.h"
class CommondDir :public Commond
{
public:
	CommondDir(CommondEnum type);
	virtual ~CommondDir();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};


#endif