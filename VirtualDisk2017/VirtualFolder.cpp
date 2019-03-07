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
bool VirtualFolder::createPath(std::list<std::string> subfiles)
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
		m_vfChildren[tmp]->SetName(tmp.c_str());
	}
	return true;
}
bool VirtualFolder::deletePath(std::list<std::string> subfiles,int s)
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
bool VirtualFolder::FindPath(std::list<std::string> subfiles)
{
	bool res = true;
	if (subfiles.size() == 0)
		return true;
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();
		if (!m_vfChildren[tmp]->IsPath())
			return false;
		if (subfiles.size() == 0)
			return true;
		res &= m_vfChildren[tmp]->FindPath(subfiles);
		return res;
	}
	else
		return false;
}
bool VirtualFolder::FindFile(std::list<std::string> subfiles)
{
	bool res = true;
	if (subfiles.empty() == 0)
		return true;
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();		
		if (subfiles.size() == 0)
		{
			if (m_vfChildren[tmp]->IsPath())
				return false;
			return true;
		}
		res &= m_vfChildren[tmp]->FindPath(subfiles);
		return res;
	}
	else
		return false;
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, std::list<std::string> subfiles, const char* dstName)
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
	vf->SetName(dstName);
	m_vfChildren[dstName] = vf;
	return true;
}
bool VirtualFolder::GetAllFile(std::list<std::string>paths, std::list<std::string>& files)
{
	if (!FindPath(paths))
		return false;
	if (m_vfChildren.find(paths.back()) != m_vfChildren.end())
	{
		auto tmp = paths.back();
		paths.pop_back();
		if (paths.size() == 0)
		{
			return m_vfChildren[tmp]->GetAllFile(files);
		}
		if (m_vfChildren[tmp]->IsPath())
		{
			return m_vfChildren[tmp]->GetAllFile(paths, files);
		}
		else
			return false;
	}
	else
		return false;
}
bool VirtualFolder::GetAllFile(std::list<std::string>& files)
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		if (!it->second->IsPath())
		{
			files.push_back(it->first);
		}
	}
	return true;
}
bool VirtualFolder::GetFileMem(std::list<std::string> srcPaths,void** mem,int &size)
{
	if (!FindFile(srcPaths))
		return false;
	if (m_vfChildren.find(srcPaths.back()) != m_vfChildren.end())
	{
		auto tmp = srcPaths.back();
		srcPaths.pop_back();
		if (srcPaths.size() == 0)
		{
			return m_vfChildren[tmp]->GetFileMem(mem, size);
		}
		if (m_vfChildren[tmp]->IsPath())
		{
			return m_vfChildren[tmp]->GetFileMem(srcPaths, mem, size);
		}
		else
			return false;
	}
	else
		return false;
}