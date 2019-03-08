#include "VirtualFile.h"
#include "StringUtil.h"
VirtualFile::VirtualFile()
{
}

VirtualFile::~VirtualFile()
{
	if (m_size > 0)
	{
		m_size = 0;
		free(m_mem);
	}
}
bool VirtualFile::SetMemory(void* mem, int memSize)
{
	if (memSize != 0)
	{
		m_size = memSize;
		m_mem = malloc(memSize);
		memcpy(m_mem, mem, memSize);
	}
	return true;
}
bool VirtualFile::GetFileMem(void** mem, int& size)
{
	if (m_size == 0)
		return false;
	*mem = m_mem;
	size = m_size;
	return true;
}
VirtualBlock* VirtualFile::GetVirtualPoint(std::list<std::string>subfiles)
{
	if (m_name == subfiles.back())
	{
		subfiles.pop_back();
		if(subfiles.size() == 0)
			return this;
	}
	return nullptr;
}
void VirtualFile::PrintMessage(int state)
{
	auto strMemsize = std::to_string(m_size);
	StringUtil::AddDot(strMemsize);
	printf("%s  %s              %19s%s\n", m_datetime, m_daytime, strMemsize.c_str(), m_name.c_str());
}