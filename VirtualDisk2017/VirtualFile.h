#ifndef _VirtualFile_H_
#define _VirtualFile_H_
#include "VirtualBlock.h"
class VirtualFile :public VirtualBlock
{
public:
	VirtualFile();
	~VirtualFile();
	virtual std::string GetDir() { return ""; }
	virtual bool createPath(std::vector<std::string> subfiles) { return false; }
	virtual bool deletePath(std::vector<std::string> subfiles, int s = 0) { return false; }
	virtual bool Init() { return __super::Init(); }
	virtual bool SetMemory(void* mem, int memSize);
	virtual bool IsPathEmpty() { return false; }
	virtual bool IsPath() { return false; }
	virtual bool FindPath(std::vector<std::string> subfiles) { return false; }
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) { return false; };
private:
	void* m_mem = nullptr;
	int m_size = 0;
};


#endif