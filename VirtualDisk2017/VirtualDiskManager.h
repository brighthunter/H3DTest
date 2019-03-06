#ifndef	_VirtualDiskManager_H_
#define _VirtualDiskManager_H_
#include <map>
#include <string>
#include <list>
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
	void GetCursor(std::string& cursor);
	void AddCursor(VirtualFolder* pvf);
	void ClearCursor();
	bool analyzeCommond(const char* userInput);
	bool createPath(const char* userInput);
	bool deletePath(const char* userInput,bool s = false);
	bool copyPath(std::string src, std::string dst);
	bool getFullPath(std::string &fullpath, const char* userInput);
	void CopyRealDiskToPath(std::string src, std::string dst);
	void Rename(const char* userInput, const char* name);
private:
	VirtualFolder * root;
	std::map<std::string,VirtualFolder*> m_vfChildren;
	CommondManager* m_pCommondmanager;
	std::string m_sdiskName;
	std::list<VirtualFolder*> m_pvfCursorlist;
};
#endif