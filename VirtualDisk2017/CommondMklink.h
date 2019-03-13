#ifndef _CommondMklink_H_
#define _CommondMklink_H_
#include "Commond.h"
class CommondMklink :public Commond
{
public:
	CommondMklink(const char* type);
	~CommondMklink();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif