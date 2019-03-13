#ifndef _CommondCopy_H_
#define _CommondCopy_H_
#include "Commond.h"
class CommondCopy :public Commond
{
public:
	CommondCopy(const char* type);
	~CommondCopy();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};

#endif