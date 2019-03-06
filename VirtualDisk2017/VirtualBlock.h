#ifndef _VirtualBlock_H_
#define _VirtualBlock_H_
#include <vector>
#include <string>
#include <map>
class VirtualBlock
{
public:
	VirtualBlock();
	virtual ~VirtualBlock() = 0;
	virtual std::string GetDir() = 0;
	virtual bool createPath(std::vector<std::string> subfiles) = 0;
	virtual bool deletePath(std::vector<std::string> subfiles, int s = 0) = 0;	
	virtual bool IsPathEmpty() = 0;
	virtual bool IsPath() = 0;
	virtual bool FindPath(std::vector<std::string> subfiles) = 0;
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) = 0;
	virtual bool Init();
protected:
	char m_datetime[32];
	char m_daytime[32];
private:
	virtual bool SetTimeNow();
};


#endif