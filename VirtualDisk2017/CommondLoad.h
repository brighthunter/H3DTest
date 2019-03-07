#ifndef _CommondLoad_H_
#define _CommondLoad_H_
#include "Commond.h"
class CommondLoad :public Commond
{
public:
	CommondLoad (CommondEnum type);
	~CommondLoad ();
	virtual bool analyzeCommond(std::list<std::string> allSubs);
private:

};


#endif // !_CommondLoad_H_
