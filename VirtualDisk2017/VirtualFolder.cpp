#include "VirtualFolder.h"
#include "VirtualFile.h"
#include "VirtualMKLink.h"
#include "VirtualDiskManagerObserver.h"
#include <Windows.h>
#include "StringUtil.h"
#include "PathUtil.h"
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
			cursor +=  it->second->GetDir();
		}
		cursor = m_name + '\\' + cursor;
		return cursor;
	}
	else
		return "";
}
bool VirtualFolder::createPath(std::list<std::string> subfiles)
{
	//new 
	if (subfiles.size() == 0)
	{
		printf("路径为空\n");
		return true;
	}
	if (m_name == subfiles.back())
	{
		subfiles.pop_back();
		auto tmp = subfiles.back();
		if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
		{
			if (subfiles.size() == 1)
			{
				printf("路径已存在\n");
				return false;
			}
			m_vfChildren[tmp]->createPath(subfiles);
		}
		else
		{
			m_vfChildren[tmp] = new VirtualFolder();
			m_vfChildren[tmp]->Init();
			m_vfChildren[tmp]->SetName(tmp.c_str());
		}
		return true;
	}
	else
	{
		return false;
	}
	
	return true;
	//old
	/*auto tmp = subfiles.back();
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{		
		subfiles.pop_back();
		m_vfChildren[tmp]->createPath(subfiles);
	}
	else
	{
		subfiles.pop_back();
		if (m_vfChildren.find(tmp) != m_vfChildren.end())
			return false;
		m_vfChildren[tmp] = new VirtualFolder();
		m_vfChildren[tmp]->Init();
		m_vfChildren[tmp]->SetName(tmp.c_str());
	}*/
	return true;
}
bool VirtualFolder::deletePath(std::list<std::string> subfiles, int s)
{
	//new
	if (subfiles.size() == 0)
	{
		printf("待删除路径为空\n");
		return false;
	}
	if (m_name == subfiles.back())
	{
		subfiles.pop_back();
		if (subfiles.size() > 1)
		{
			auto tmp = subfiles.back();
			if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
			{
				m_vfChildren[tmp]->deletePath(subfiles,s);
				
			}
			return true;
		}
		else if (subfiles.size() == 1)
		{			
			auto tmp = subfiles.back();
			if (m_vfChildren[tmp]->IsPathEmpty())
				delete m_vfChildren[tmp];
			else if (s & 1)
			{
				subfiles.push_back(tmp);
				m_vfChildren[tmp]->deletePath(subfiles, s);
			}
			return true;
		}
		else if (subfiles.size() == 0)
		{
			printf("无法删除盘符路径\n");
			return false;
		}
	}
	//old
	/*auto tmp = subfiles.back();	
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		subfiles.pop_back();
		m_vfChildren[tmp]->deletePath(subfiles);
		if (!subfiles.size())
		{
			if(m_vfChildren[tmp]->IsPathEmpty())
				delete m_vfChildren[tmp];
			else if (s & 1)
			{
				subfiles.push_back(tmp);
				m_vfChildren[tmp]->deletePath(subfiles,s);
			}
		}
	}
	*/
	return true;
}
bool VirtualFolder::DeleteVirtualFile(std::list<std::string> subfiles,int s)
{	//new
	if (m_name == subfiles.back())
	{
		auto p = GetVirtualPoint(subfiles);
		if (!p)
		{
			printf("删除路径不存在\n");
			return false;
		}
		if(p->IsPathEmpty())
			p->DeleteVirtualFile(s);
		else
		{
			printf("删除路径非法");
			return false;
		}
	}
	return true;
	//old
	/*auto tmp = subfiles.back();
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		subfiles.pop_back();
		m_vfChildren[tmp]->DeleteVirtualFile(subfiles, s);
		if (!subfiles.size())
		{
			if (!m_vfChildren[tmp]->IsPathEmpty())
			{
				m_vfChildren[tmp]->DeleteVirtualFile(s);
			}
		}
	}
	else
	{
		printf("%s找不到\n", subfiles.back().c_str());
		return false;
	}
*/
	return true;
}
bool VirtualFolder::DeleteVirtualFile(int s)
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		if (!it->second->IsPath())
		{
			delete it->second;
			it = m_vfChildren.erase(it);
		}
		else
		{
			if (s & 1)
			{
				it->second->DeleteVirtualFile(s);
			}
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
bool VirtualFolder::IsRoot()
{
	if (m_broot)
		return true;
	else
		return false;
}
bool VirtualFolder::FindPath(std::list<std::string> subfiles)
{
	//new
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("磁盘路径不存在\n");
		return false;
	}
	if (p->IsPath())
		return true;
	else
		return false;
	//old
	/*bool res = true;
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
		return false;*/
}
bool VirtualFolder::FindFile(std::list<std::string> subfiles)
{
	//new
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("文件路径不存在\n");
		return false;
	}
	if (!p->IsPath())
		return true;
	else
	{
		return false;
	}
	//old
	/*bool res = true;
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
		return false;*/
}
bool VirtualFolder::FindPathFile(std::list<std::string> subfiles)
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
			return true;
		}
		res &= m_vfChildren[tmp]->FindPathFile(subfiles);
		return res;
	}
	else
		return false;
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, std::list<std::string> subfiles, const char* dstName)
{
	//new
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		auto dstfileName = subfiles.front();
		subfiles.pop_front();
		auto fatherPath = subfiles.front();
		printf("虚拟文件%s的父路径%s不存在\n", dstfileName.c_str(), fatherPath.c_str());
		return false;
	}
	if (p->IsPath())
	{
		p->CreateVirtualFile(mem, fsize, dstName);
		return true;
	}
	else
	{
		printf("路径非法\n");
		return false;
	}
	//old
	/*bool res = true;
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
		return false;*/
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, const char* dstName)
{
	if (m_vfChildren.find(dstName) != m_vfChildren.end())
		return false;
	auto vf = new VirtualFile();
	vf->SetMemory(mem,fsize);
	vf->SetName(dstName);
	m_vfChildren[dstName] = vf;
	return true;
}
bool VirtualFolder::GetAllFile(std::list<std::string>paths, std::list<std::string>& files)
{
	//new 
	auto p = GetVirtualPoint(paths);
	if (!p)
	{
		printf("路径不存在\n");
		return false;
	}
	else
	{
		return p->GetAllFile(files);
	}
	//old
	/*if (!FindPath(paths))
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
		return false;*/
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
	//new
	auto p = GetVirtualPoint(srcPaths);
	if (!p)
	{
		printf("路径不存在\n");
		return false;
	}
	p->GetFileMem(mem, size);
	return true;
	//old
	/*if (!FindFile(srcPaths))
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
		return false;*/
}
bool VirtualFolder::RenamePathFile(const char* name, std::list<std::string>subfiles)
{
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("重命名路径文件不存在\n");
		return false;
	}
	else
	{
		p->SetName(name);
		return true;
	}
	//old
/*
	if (!FindPathFile(subfiles))
		return false;
	if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();
		if (subfiles.size() == 0)
		{
			m_vfChildren[tmp]->SetName(name);
		}
		if (m_vfChildren[tmp]->IsPath())
		{
			return m_vfChildren[tmp]->RenamePathFile(name, subfiles);
		}
		else
			return false;
	}
	else
		return false;*/
}
bool VirtualFolder::SetCursor(std::list<std::string>subfiles)
{
	if (!FindPath(subfiles))
		return false;
	else
		ClearCursor();
	//new
	VirtualBlock *p = this;
	std::list<std::string> tmpfiles;
	tmpfiles.push_front(subfiles.back());
	subfiles.pop_back();
	while (subfiles.size() > 0)
	{		
		tmpfiles.push_front(subfiles.back());
		subfiles.pop_back();
		p = p->GetVirtualPoint(tmpfiles);
		p->SetCursor();
		tmpfiles.pop_back();
	}
	return true;
	//old
	/*if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	{
		auto tmp = subfiles.back();
		subfiles.pop_back();
		if (subfiles.size() == 0)
		{
			m_vfChildren[tmp]->SetCursor();
		}
		if (m_vfChildren[tmp]->IsPath())
		{
			m_bCursor = true;
			return m_vfChildren[tmp]->SetCursor(subfiles);
		}
		else
			return false;
	}
	else
		return false;*/
}
bool VirtualFolder::SetCursor()
{
	m_bCursor = true;
	return true;
}
bool VirtualFolder::ClearCursor()
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		it->second->ClearCursor();
	}
	if(!m_broot)
		m_bCursor = false;
	return true;
}
bool VirtualFolder::PrintDir(std::list<std::string>subfiles, int state)
{
	auto p = GetVirtualPoint(subfiles);
	
	if (!p)
	{
		printf("路径不存在\n");
		return false;
	}
	subfiles.pop_back();
	if (p->IsPath())
	{
		p->PrintMessage(subfiles,state);
	}
	else 
	{
		p->PrintMessage(subfiles);
	}

	//if (!FindPath(subfiles))
	//	return false;
	//
	//if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
	//{
	//	auto tmp = subfiles.back();
	//	subfiles.pop_back();
	//	if (subfiles.size() == 0)
	//	{
	//		//m_vfChildren[tmp]->PrintDir(bgSubsize);
	//	}
	//	if (m_vfChildren[tmp]->IsPath())
	//	{
	//		//return m_vfChildren[tmp]->PrintDir(subfiles, bgSubsize);
	//	}
	//	else
	//		return false;
	//}
	return false;
	
}
VirtualBlock* VirtualFolder::GetVirtualPoint(std::list<std::string>subfiles)
{
	auto tmptest = subfiles.back();
	if (m_name == subfiles.back())
	{
		subfiles.pop_back();
		if (subfiles.empty())
			return this;
		if (m_vfChildren.find(subfiles.back()) != m_vfChildren.end())
		{
			return m_vfChildren[subfiles.back()]->GetVirtualPoint(subfiles);
		}
		else
			return nullptr;
	}
	else
	{
		printf("名字不匹配\n");
		return nullptr;
	}

	 
}
void VirtualFolder::PrintPathMessage(bool hasName)
{
	if (!hasName)
	{
		printf("%s  %s    <DIR>          .\n",m_datetime,m_daytime);
		printf("%s  %s    <DIR>          ..\n",m_datetime,m_daytime);
	}
	else
	{
		printf("%s  %s    <DIR>          %s\n", m_datetime, m_daytime, m_name.c_str());
	}
}
void VirtualFolder::PrintMessage(std::list<std::string> subfiles,int state)
{
	std::string printPath;
	for (auto it = subfiles.begin(); it != subfiles.end(); it++)
	{
		printPath += *it + "\\" ;
	}
	printPath += m_name;
	printf("\n%s的目录\n\n", printPath.c_str());
	if (!IsRoot())
	{
		PrintPathMessage(false);
	}
	int fileNum = 0;
	int dirNum = 0;
	int allfileSize = 0;
	std::list<VirtualBlock*> subDirs;
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		if (it->second->IsPath())
		{
			if (state & 0x1)
			{
				subDirs.push_back(it->second);
			}
			it->second->PrintPathMessage(true);
			++dirNum;
		}
		else
		{
			if (!(state & 0x10))
			{
				it->second->PrintMessage(subfiles,state);
				int size = it->second->GetFileSzie();
				allfileSize += size;
				++fileNum;
			}
		}
	}
	MEMORYSTATUSEX sysMemStatus;
	sysMemStatus.dwLength = sizeof(sysMemStatus);
	if (!GlobalMemoryStatusEx(&sysMemStatus))
	{
		printf("GlobalMemoryStatusEx fail\n");
		sysMemStatus.ullTotalVirtual = 0;
	}
	std::string ullstr = std::to_string(sysMemStatus.ullTotalVirtual);
	StringUtil::AddDot(ullstr);
	printf("               %d 个文件%19d 字节\n", fileNum, allfileSize);
	printf("               %d 个目录%19s 可用字节\n", fileNum, ullstr.c_str());
	for (auto it = subDirs.begin(); it != subDirs.end(); it++)
	{
		(*it)->PrintMessage(subfiles,state);
	}
}
bool VirtualFolder::MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root)
{
	if (dst.size() == 0)
	{
		printf("路径为空\n");
		return false;
	}
	if (m_name == dst.back())
	{
		dst.pop_back();
		auto tmp = dst.back();
		if (m_vfChildren.find(dst.back()) != m_vfChildren.end())
		{
			if (dst.size() == 1)
			{
				printf("路径已存在\n");
				return false;
			}
			m_vfChildren[tmp]->MkLink(src,dst, root);
		}
		else
		{
			auto link = new VirtualMKLink();
			link->Init(src, root);
			link->SetName(tmp.c_str());
			m_vfChildren[tmp] = link;
		}
		return true;
	}
	else
	{
		return false;
	}

	return true;
}
void VirtualFolder::Save(std::string dst)
{
	std::string dstPath;
	if (m_broot)
	{
		dstPath = dst + std::string("/") + "v";
	}
	else
	{
		dstPath = dst + std::string("/") + m_name;
	}
	CreateDirectory(dstPath.c_str(),NULL);
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		it->second->Save(dstPath);
	}
}
void VirtualFolder::Load(std::string src)
{
	std::list<std::string> allFiles;
	PathUtil::GetAllDirAndFiles(src, allFiles);
	return;
}
void VirtualFolder::Clear()
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		it->second->Clear();
		delete it->second;
	}
	m_vfChildren.clear();
}
void VirtualFolder::Move(std::list<std::string> src,std::list<std::string> dst, int state)
{
	auto psrc = GetVirtualPoint(src);
	if (!psrc)
	{
		printf("移动源路径不存在\n");
		return;
	}
	auto pdst = GetVirtualPoint(dst);
	if (!pdst)
	{
		printf("移动目的路径不存在\n");
		return;
	}
	src.pop_front();
	auto psrcfather = GetVirtualPoint(src);
	pdst->CopyForMove(psrc, state);
	if (!psrc->GetChildrenSize())
	{
		psrcfather->EraseChild(psrc->GetName());	
	}
}
void VirtualFolder::EraseChild(std::string cname)
{
	if (m_vfChildren.find(cname) == m_vfChildren.end())
		return;
	m_vfChildren.erase(cname);

}
void VirtualFolder::CopyForMove(VirtualBlock* pchild,int state)
{
	if (m_vfChildren.find(pchild->GetName()) != m_vfChildren.end())
	{
		if (pchild->IsPath() && m_vfChildren[pchild->GetName()]->IsPath())
		{
			m_vfChildren[pchild->GetName()]->Combine(pchild, state);
		
		}
		else if(state &0x1)
		{
			delete m_vfChildren[pchild->GetName()];
			m_vfChildren[pchild->GetName()] = pchild;
		}
		else
		{

		}
	}
	else
	{
		m_vfChildren[pchild->GetName()] = pchild;
	}
}

void VirtualFolder::ClearMap()
{
	m_vfChildren.clear();
}
int VirtualFolder::GetChildrenSize()
{
	return m_vfChildren.size();
}
void VirtualFolder::Combine(VirtualBlock* pComb, int state)
{
	 VirtualFolder* p = (VirtualFolder*)pComb;
	 std::list<VirtualBlock*> clist;
	 p->GetChildren(clist);
	 for (auto it = clist.begin(); it != clist.end(); it++)
	 {
		 if (m_vfChildren.find((*it)->GetName()) != m_vfChildren.end())
		 {
			 m_vfChildren[(*it)->GetName()]->CopyForMove(*it, state);
			 if (!(*it)->GetChildrenSize())
			 {
				 p->EraseChild((*it)->GetName());
			 }	
		 }
		 else
		 {
			 m_vfChildren[(*it)->GetName()] = *it;
		 }
	 }
}
void VirtualFolder::GetChildren(std::list<VirtualBlock*> &pchildren)
{
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		pchildren.push_back(it->second);
	}
}