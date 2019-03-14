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
#include "CommondSaf.h"
#include "CommondLod.h"
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
			Commond* p = new CommondDir("dir");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MD:
		{
			Commond* p = new CommondMd("md");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_Rd:
		{
			Commond* p = new CommondRd("rd");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_CD:
		{
			Commond* p = new CommondCD("cd");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_DEL:
		{
			Commond* p = new CommondDel("del");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_COPY:
		{
			Commond* p = new CommondCopy("copy");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_REN:
		{
			Commond* p = new CommondRen("ren");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MOVE:
		{
			Commond* p = new CommondMove("move");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_MKLINK:
		{
			Commond* p = new CommondMklink("mklink");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_SAVE:
		{
			Commond* p = new CommondSave("save");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_LOAD:
		{
			Commond* p = new CommondLoad("load");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_CLS:
		{
			Commond* p = new CommondCls("cls");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_Saf:
		{
			Commond* p = new CommondSaf("saf");
			m_CommondsVec.push_back(p);
			break;
		}
		case COMMOND_Lod:
		{
			Commond* p = new CommondLod("lod");
			m_CommondsVec.push_back(p);
			break;
		}
		default:
		{
			printf("%d枚举类型没有初始化\n", i);
		}
			break;
		}
	}
	return true;
}
bool CommondManager::analyzeCommond(const char* userInput)
{
	std::list<std::string> allSubs;
	PathUtil::SeperatePath(userInput, allSubs); 
	std::string commondName = userInput; 
	if (allSubs.size() == 0)
		return true;
	bool res = false;
	for (size_t i = 0; i != COMMOND_END; i++)
	{
		res |= m_CommondsVec[i]->analyzeCommondType(allSubs);
	}
	if (!res)
		printf("[%s] 命令未定义\n", allSubs.back().c_str());
	return res;
	/*if (allSubs.back() == "dir")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_DIR]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "md")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_MD]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "rd")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_Rd]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "cd")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_CD]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "del")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_DEL]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "copy")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_COPY]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "ren")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_REN]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "move")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_MOVE]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "mklink")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_MKLINK]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "save")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_SAVE]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "load")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_LOAD]->analyzeCommond(allSubs);
	}
	else if (allSubs.back() == "cls")
	{
		allSubs.pop_back();
		return 	m_CommondsVec[COMMOND_CLS]->analyzeCommond(allSubs);
	}
	else
	{
		printf("未知命令\n");
		return false;
	}*/
}