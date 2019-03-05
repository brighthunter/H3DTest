#ifndef _CommondCls_H_
#define _CommondCls_H_
#include "Commond.h"
class CommondCls :public Commond
{
public:
	CommondCls(CommondEnum type);
	~CommondCls();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};


#endif