#ifndef _CommondCD_H_
#define _CommondCD_H_
#include "Commond.h"
class CommondCD :public Commond
{
public:
	CommondCD(const char*);
	~CommondCD();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};



#endif