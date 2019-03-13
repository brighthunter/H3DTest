#ifndef _CommondDel_H_
#define _CommondDel_H_
#include "Commond.h"
class CommondDel :public Commond
{
public:
	CommondDel(const char* type);
	~CommondDel();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif