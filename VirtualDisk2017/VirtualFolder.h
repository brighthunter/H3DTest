#ifndef _VirtualFolder_H_
#define _VirtualFolder_H_
#include <vector>
#include <string>
#include <map>
class VirtualFolder
{
public:
	VirtualFolder(void);
	~VirtualFolder(void);
	const char* GetDir();
private:
	std::map<std::string,VirtualFolder*> m_vfChildren;
	bool m_bCursor = false;
	std::string datetime;
	std::string daytime;
	void* mem = nullptr;
	int size = 0;
};
#endif