#ifndef _CommondManager_H_
#define _CommondManager_H_
#include <vector>
#include "Commond.h"
class CommondManager
{
public:
	CommondManager(void);
	~CommondManager(void);
	bool Init();
	bool analyzeCommond(const char* userInput);
private:
	std::vector<Commond*> m_CommondsVec;
};
#endif