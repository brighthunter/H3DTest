#include "VirtualFolder.h"
#include "VirtualFile.h"
#include "VirtualDiskManagerObserver.h"

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
std::string VirtualFolder::GetDir()
{
	std::string cursor;
	if (m_bCursor)
	{
		for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
		{
			cursor += it->second->GetDir();
		}
		return cursor;
	}
	else
		return "";
}
bool VirtualFolder::createPath(std::vector<std::string> subfiles)
{
	auto tmp = subfiles.back();
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{		
		subfiles.pop_back();
		m_vfChildren[tmp]->createPath(subfiles);
	}
	else
	{
		subfiles.pop_back();
		m_vfChildren[tmp] = new VirtualFolder();
		m_vfChildren[tmp]->Init();
	}
	return true;
}
bool VirtualFolder::deletePath(std::vector<std::string> subfiles,int s)
{
	auto tmp = subfiles.back();
	if (s & 1)
	{
		deletePath(subfiles);
	}
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		subfiles.pop_back();
		m_vfChildren[tmp]->deletePath(subfiles);
		if (!subfiles.size())
		{
			if(m_vfChildren[tmp]->IsPathEmpty())
				delete m_vfChildren[tmp];
		}
	}
	
	return true;
}
bool VirtualFolder::Init()
{
	__super::Init();
	return true;
}

bool VirtualFolder::IsPathEmpty()
{
	if (IsPath() && !m_vfChildren.size())
		return true;
	return false;
}
bool VirtualFolder::IsPath()
{
	return true;
}
bool VirtualFolder::FindPath(std::vector<std::string> subfiles)
{
	bool res = true;
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();
		if (subfiles.size() == 0)
			return true;
		res &= m_vfChildren[tmp]->FindPath(subfiles);
		return res;
	}
	else
		return false;
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, std::vector<std::string> subfiles, const char* dstName)
{
	bool res = true;
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();
		if (subfiles.size() == 0)
		{
			res &= m_vfChildren[tmp]->CreateVirtualFile(mem, fsize, dstName);
			return res;
		}
		res &= m_vfChildren[tmp]->FindPath(subfiles);
		return res;
	}
	else
		return false;
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, const char* dstName)
{
	auto vf = new VirtualFile();
	vf->SetMemory(mem,fsize);
	m_vfChildren[dstName] = vf;
	return true;
}
