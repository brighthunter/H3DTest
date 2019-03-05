#ifndef _CommondCopy_H_
#define _CommondCopy_H_
#include "Commond.h"
class CommondCopy :public Commond
{
public:
	CommondCopy(CommondEnum type);
	~CommondCopy();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};

#endif