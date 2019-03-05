#ifndef _CommondDel_H_
#define _CommondDel_H_
#include "Commond.h"
class CommondDel :public Commond
{
public:
	CommondDel(CommondEnum type);
	~CommondDel();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};


#endif