#ifndef	_VirtualDiskManager_H_
#define _VirtualDiskManager_H_
#include <map>
#include <string>
#include "VirtualFolder.h"
#include "CommondManager.h"
class VirtualDiskManager
{
public:
	void RegisterCallback();
	bool Init();
	VirtualDiskManager(void);
	~VirtualDiskManager(void);
	void PrintCursor();
	const char* GetCursor();
	bool analyzeCommond(const char* userInput);
private:
	std::map<std::string,VirtualFolder*> m_vfChildren;
	CommondManager* m_pCommondmanager;
	std::string m_diskName;
};
#endif