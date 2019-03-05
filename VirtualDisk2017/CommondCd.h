#ifndef _CommondCD_H_
#define _CommondCD_H_
#include "Commond.h"
class CommondCD :public Commond
{
public:
	CommondCD(CommondEnum type);
	~CommondCD();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};



#endif