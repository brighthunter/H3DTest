#ifndef _CommondMd_H_
#define _CommondMd_H_
#include "Commond.h"
class CommondMd :public Commond
{
public:
	CommondMd(const char* type);
	~CommondMd();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif // ! CommondMd
