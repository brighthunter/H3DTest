#ifndef _CommondRd_H_
#define _CommondRd_H_
#include "Commond.h"
class CommondRd :public Commond
{
public:
	CommondRd(const char* type);
	~CommondRd();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif // CommondRd
