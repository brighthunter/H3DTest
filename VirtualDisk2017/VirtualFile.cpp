#include "VirtualFile.h"
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