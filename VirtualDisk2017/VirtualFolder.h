#ifndef _VirtualFolder_H_
#define _VirtualFolder_H_
#include "VirtualBlock.h"

class VirtualFolder :public VirtualBlock
{
public:
	VirtualFolder(void);
	~VirtualFolder(void);
	virtual std::string GetDir();
	virtual bool createPath(std::list<std::string> subfiles);
	virtual bool deletePath(std::list<std::string> subfiles,int s = 0);
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles,int s = 0);
	virtual bool DeleteVirtualFile(int s);
	virtual bool Init();
	virtual bool IsPathEmpty();
	virtual bool IsPath();
	virtual bool IsRoot();
	virtual bool FindPath(std::list<std::string> subfiles);
	virtual bool FindFile(std::list<std::string> subfiles);
	virtual bool FindPathFile(std::list<std::string> subfiles);
	virtual bool CreateVirtualFile(void *mem,int fsize, std::list<std::string> virtualFiles,const char* dstName);
	virtual bool CreateVirtualFile(void *mem,int fsize,const char* dstName);
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files);
	virtual bool GetAllFile(std::list<std::string>& files);
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size);
	virtual bool GetFileMem(void** mem, int& size) { return false; }
	virtual int  GetFileSzie() { return 0; }
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles);
	virtual bool SetCursor(std::list<std::string> subfiles);
	virtual bool SetCursor();
	virtual bool ClearCursor();
	virtual bool PrintDir(std::list<std::string>subfiles, int state);
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles);
	virtual void SetRoot(bool broot) { m_broot = broot; m_bCursor = true; }
	virtual void PrintPathMessage(bool hasName);
	virtual void PrintMessage(int state);
private:
	std::map<std::string, VirtualBlock*> m_vfChildren;
	bool m_bCursor = false;
	bool m_broot = false;
	
	
};
#endif