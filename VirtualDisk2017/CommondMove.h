#ifndef _CommondMove_H_
#define _CommondMove_H_
#include "Commond.h"
class CommondMove :public Commond
{
public:
	CommondMove(CommondEnum type);
	~CommondMove();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};



#endif