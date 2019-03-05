#include "CommondManager.h"
#include "CommondDir.h"
#include "CommondMd.h"
#include "CommondRd.h"
#include "CommondCd.h"
#include "CommondDel.h"
#include "CommondCopy.h"
#include "CommondRen.h"
#include "CommondMove.h"
#include "CommondMklink.h"
#include "CommondSave.h"
#include "CommondLoad.h"
#include "CommondCls.h"
#include "PathUtil.h"
CommondManager::CommondManager(void)
{
}

CommondManager::~CommondManager(void)
{
}
bool CommondManager::Init()
{
	for (size_t i = 0; i < COMMOND_END; i++)
	{
		switch (i)
		{
		case COMMOND_DIR:
		{
			Commond* p = new CommondDir(COMMOND_DIR);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MD:
		{
			Commond* p = new CommondMd(COMMOND_MD);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_Rd:
		{
			Commond* p = new CommondRd(COMMOND_Rd);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_CD:
		{
			Commond* p = new CommondCD(COMMOND_CD);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_DEL:
		{
			Commond* p = new CommondDel(COMMOND_DEL);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_COPY:
		{
			Commond* p = new CommondCopy(COMMOND_COPY);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_REN:
		{
			Commond* p = new CommondRen(COMMOND_REN);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MOVE:
		{
			Commond* p = new CommondMove(COMMOND_MOVE);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MKLINK:
		{
			Commond* p = new CommondMklink(COMMOND_MKLINK);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_SAVE:
		{
			Commond* p = new CommondSave(COMMOND_SAVE);
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_LOAD:
		{
			Commond* p = new CommondLoad(COMMOND_LOAD);
			m_CommondsVec.push_back(p);
			break;
		}
		default:
			break;
		}
	}
	return true;
}
bool CommondManager::analyzeCommond(const char* userInput)
{
	std::vector<std::string> allSubs;
	PathUtil::SeperatePath(userInput, allSubs); 
	std::string commondName = userInput; 
	if (*allSubs.begin() == "dir")
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_DIR]->analyzeCommond(allSubs);
	}
	else if (*allSubs.begin() == "md")
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_MD]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0,2,"rd"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_Rd]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 2, "cd"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_CD]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 3,"del"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_DEL]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 4, "copy"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_COPY]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 3, "ren"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_REN]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 4, "move"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_MOVE]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 6, "mklink"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_MKLINK]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 4, "save"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_SAVE]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 4, "load"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_LOAD]->analyzeCommond(allSubs);
	}
	else if (commondName.compare(0, 3, "cls"))
	{
		allSubs.erase(allSubs.begin());
		return 	m_CommondsVec[COMMOND_CLS]->analyzeCommond(allSubs);
	}
	else
		return false;
}