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
	void GetCursorWithoutRoot(std::string& cursor);
	void AddCursor(const char* path);
	void ClearCursor();
	void PrintDir(const char* userInput,int state);
	bool analyzeCommond(const char* userInput);
	bool CreateVirtualPath(const char* userInput);
	bool DeleteVirtualPath(const char* userInput,bool s = false);
	bool copyPath(std::string src, std::string dst);
	bool CopyPath(std::string src, std::string dst);
	bool getFullPath(std::string &fullpath, const char* userInput);
	bool getFullPathWithoutRoot(std::string &fullpath, const char* userInput);
	//Copy
	bool CopyRealDiskToVirtual(std::string src, std::string dst);
	bool CopyVirtualToRealDisk(std::string src, std::string dst);
	bool CopyRealDiskToRealDisk(std::string src, std::string dst);
	bool CopyVirtualToVirtual(std::string src, std::string dst);
	void Rename(const char* userInput, const char* name);
	void SetCursor(const char* userInput);
	void DeleteVirtualFile(const char* userInput,int s);
	//Mklink
	void MkLink(const char* src, const char* dst);
	void Save(const char* dst);
	void Load(const char* src);
	void Move(const char* src, const char* dst,int state);
private:
	VirtualFolder * m_root;
	CommondManager* m_pCommondmanager;
	std::string m_sdiskName;
};
#endif