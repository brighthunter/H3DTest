#ifndef _CommondSaf_H_
#define _CommondSaf_H_
#include "Commond.h"
class CommondSaf :public Commond
{
public:
	CommondSaf(const char* type);
	~CommondSaf();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif