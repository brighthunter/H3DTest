#include "VirtualFile.h"
VirtualFile::VirtualFile()
{
}

VirtualFile::~VirtualFile()
{
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