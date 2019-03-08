#ifndef _VirtualBlock_H_
#define _VirtualBlock_H_
#include <string>
#include <map>
#include <list>
class VirtualBlock
{
public:
	VirtualBlock();
	virtual ~VirtualBlock() = 0;
	virtual std::string GetDir() = 0;
	virtual bool createPath(std::list<std::string> subfiles) = 0;
	virtual bool deletePath(std::list<std::string> subfiles, int s = 0) = 0;
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles, int s = 0) = 0;
	virtual bool DeleteVirtualFile(int s) = 0;
	virtual bool IsPathEmpty() = 0;
	virtual bool IsPath() = 0;
	virtual bool IsRoot() = 0;
	virtual bool FindPath(std::list<std::string> subfiles) = 0;
	virtual bool FindPathFile(std::list<std::string> subfiles) = 0;
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) = 0;
	virtual bool Init();
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files) = 0;
	virtual bool GetAllFile(std::list<std::string>& files) = 0;
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size) = 0;
	virtual bool GetFileMem(void** mem, int& size) = 0;
	virtual int  GetFileSzie() = 0;
	virtual void SetName(const char* name) { m_name = name; }
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles) = 0;
	virtual bool SetCursor(std::list<std::string>subfiles) = 0;
	virtual bool SetCursor() = 0;
	virtual bool ClearCursor() = 0;
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles) = 0;
	virtual void PrintPathMessage(bool hasName) = 0;
	virtual void PrintMessage(int state = 0) = 0;
protected:
	char m_datetime[32];
	char m_daytime[32];
	std::string m_name;
private:
	virtual bool SetTimeNow();
};


#endif