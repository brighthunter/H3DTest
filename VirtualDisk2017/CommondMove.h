#ifndef _CommondMove_H_
#define _CommondMove_H_
#include "Commond.h"
class CommondMove :public Commond
{
public:
	CommondMove(const char* type);
	~CommondMove();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};



#endif