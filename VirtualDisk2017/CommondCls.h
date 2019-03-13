#ifndef _CommondCls_H_
#define _CommondCls_H_
#include "Commond.h"
class CommondCls :public Commond
{
public:
	CommondCls(const char* type);
	~CommondCls();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif