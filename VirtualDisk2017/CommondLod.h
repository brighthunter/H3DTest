#ifndef _CommondLod_H_
#define _CommondLod_H_
#include "Commond.h"
class CommondLod :public Commond
{
public:
	CommondLod(const char* type);
	~CommondLod();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif // !_CommondLod_H_
