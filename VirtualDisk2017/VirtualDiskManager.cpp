#include "VirtualDiskManager.h"
#include "Tool/functor.h"
VirtualDiskManager::VirtualDiskManager(void)
{
}

VirtualDiskManager::~VirtualDiskManager(void)
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		delete it->second;
	}
	m_vfChildren.clear();
}

void VirtualDiskManager::RegisterCallback()
{
	
}
bool VirtualDiskManager::Init()
{
	bool res = true;
	m_pCommondmanager = new CommondManager();
	res &= m_pCommondmanager->Init();
	m_diskName = "v:\\";
	return res;
}
void VirtualDiskManager::PrintCursor()
{
	std::string cursor;
	cursor += m_diskName;
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{		
		cursor += it->second->GetDir();	
	}
	cursor += ">";
	printf(cursor.c_str());
}
const char* VirtualDiskManager::GetCursor()
{
	std::string cursor;
	cursor += m_diskName;
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		cursor += it->second->GetDir();
	}
	cursor += ">";
	return cursor.c_str();
}
bool VirtualDiskManager::analyzeCommond(const char* userInput)
{
	if (!m_pCommondmanager)
		return false;
	std::string Input;
	return m_pCommondmanager->analyzeCommond(userInput);
	
}