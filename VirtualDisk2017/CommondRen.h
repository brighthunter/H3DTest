#ifndef _CommondRen_H_
#define _CommondRen_H_
#include "Commond.h"
class CommondRen :public Commond
{
public:
	CommondRen(CommondEnum type);
	~CommondRen();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};

#endif