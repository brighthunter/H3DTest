#include "VirtualFolder.h"

VirtualFolder::VirtualFolder(void)
{
}

VirtualFolder::~VirtualFolder(void)
{
	
	for(auto it = m_vfChildren.begin();it != m_vfChildren.end();it++)
	{
		delete it->second;
	}
	m_vfChildren.clear();
}
const char* VirtualFolder::GetDir()
{
	std::string cursor;
	if (m_bCursor)
	{
		for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
		{
			cursor += it->second->GetDir();
		}
		return cursor.c_str();
	}
	else
		return "";
}