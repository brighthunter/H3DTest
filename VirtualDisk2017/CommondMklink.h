#ifndef _CommondMklink_H_
#define _CommondMklink_H_
#include "Commond.h"
class CommondMklink :public Commond
{
public:
	CommondMklink(CommondEnum type);
	~CommondMklink();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};


#endif