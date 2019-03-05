#ifndef _CommondRd_H_
#define _CommondRd_H_
#include "Commond.h"
class CommondRd :public Commond
{
public:
	CommondRd(CommondEnum type);
	~CommondRd();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};


#endif // CommondRd
