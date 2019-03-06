#ifndef _VirtualFolder_H_
#define _VirtualFolder_H_
#include "VirtualBlock.h"

class VirtualFolder :public VirtualBlock
{
public:
	VirtualFolder(void);
	~VirtualFolder(void);
	virtual std::string GetDir();
	virtual bool createPath(std::vector<std::string> subfiles);
	virtual bool deletePath(std::vector<std::string> subfiles,int s = 0);
	virtual bool Init();
	virtual bool IsPathEmpty();
	virtual bool IsPath();
	virtual bool FindPath(std::vector<std::string> subfiles);
	virtual bool CreateVirtualFile(void *mem,int fsize, std::vector<std::string> virtualFiles,const char* dstName);
	virtual bool CreateVirtualFile(void *mem,int fsize,const char* dstName);
private:
	std::map<std::string, VirtualBlock*> m_vfChildren;
	bool m_bCursor = false;
	
	
};
#endif