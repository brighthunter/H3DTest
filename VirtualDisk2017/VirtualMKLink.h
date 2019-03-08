#ifndef _VirtualMKLink_H_
#define _VirtualMKLink_H_
#include "VirtualFolder.h"
class VirtualMKLink :public VirtualFolder
{
public:
	VirtualMKLink();
	~VirtualMKLink();
	virtual std::string GetDir() { return ""; };
	virtual bool createPath(std::list<std::string> subfiles) { return false; }
	virtual bool deletePath(std::list<std::string> subfiles, int s = 0) { return false; }
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles, int s = 0) { return false; }
	virtual bool DeleteVirtualFile(int s) { return false; }
	virtual bool IsPathEmpty() { return false; }
	virtual bool IsPath() { return false; }
	virtual bool IsRoot() { return false; }
	virtual bool FindPath(std::list<std::string> subfiles) { return false; }
	virtual bool FindPathFile(std::list<std::string> subfiles) { return false; }
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) { return false; }
	virtual bool Init() { return true; }
	/*virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files);
	virtual bool GetAllFile(std::list<std::string>& files) ;
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size) ;
	virtual bool GetFileMem(void** mem, int& size);
	virtual int  GetFileSzie();
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles);
	virtual bool SetCursor(std::list<std::string>subfiles);
	virtual bool SetCursor();
	virtual bool ClearCursor();
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles);
	virtual void PrintPathMessage(bool hasName);
	virtual void PrintMessage(int state = 0);*/
private:
	VirtualBlock* m_root;
	std::list<std::string> m_paths;
};



#endif