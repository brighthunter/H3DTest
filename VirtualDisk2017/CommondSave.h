#ifndef _CommondSave_H_
#define _CommondSave_H_
#include "Commond.h"
class CommondSave :public Commond
{
public:
	CommondSave(CommondEnum type);
	~CommondSave();
	virtual bool analyzeCommond(std::vector<std::string> allSubs);
private:

};



#endif