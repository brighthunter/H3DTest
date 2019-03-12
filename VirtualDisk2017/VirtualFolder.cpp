#include "VirtualFolder.h"
#include "VirtualFile.h"
#include "VirtualMKLink.h"
#include "VirtualDiskManagerObserver.h"
#include <Windows.h>
#include "StringUtil.h"
#include "PathUtil.h"
#include "tinyxml2/tinyxml2.h"
#include <fstream>
#define VIRTUALDISK_HEAD "@VritualDisk"
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
std::string VirtualFolder::GetDir(bool linkCursor)
{
	std::string cursor;
	if (m_bCursor)
	{
		for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
		{
			cursor += it->second->GetDir();
		}
		cursor = m_name + '\\' + cursor;
		return cursor;
	}
	else if (linkCursor)
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
bool VirtualFolder::CreateVirtualPath(std::list<std::string> subfiles)
{
	if (subfiles.size() == 0)
	{
		printf("·��Ϊ��\n");
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
				printf("·���Ѵ���\n");
				return false;
			}
			m_vfChildren[tmp]->CreateVirtualPath(subfiles);
		}
		else
		{
			m_vfChildren[tmp] = new VirtualFolder();
			m_vfChildren[tmp]->Init(this);
			m_vfChildren[tmp]->SetName(tmp.c_str());
		}
		return true;
	}
	else
	{
		return false;
	}
	
	return true;
}
bool VirtualFolder::DeleteVirtualPath(std::list<std::string> subfiles, int s)
{
	if (m_name == subfiles.back())
	{
		auto tmpfile = subfiles.front();
		subfiles.pop_front();
		auto p = GetVirtualPoint(subfiles);
		if (!p)
		{
			printf("ɾ��·��������\n");
			return false;
		}
		p->DeleteVirtualPath(tmpfile, s);
	}
	return true;
}
bool VirtualFolder::DeleteVirtualPath(std::string pathname, int s)
{
	std::list<std::string> allchidren;
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		allchidren.push_back(it->first);
		if (s & 0x1)
		{
			if (it->second->IsPath() && !it->second->IsPathEmpty())
				it->second->DeleteVirtualPath(pathname, s);
		}
	}
	PathUtil::FindWildcard(allchidren, pathname);
	for (auto it = allchidren.begin(); it != allchidren.end(); it++)
	{
		if (m_vfChildren[*it]->IsPathEmpty())
		{
			delete m_vfChildren[*it];
			m_vfChildren.erase(*it);
		}
		else
		{
			continue;
		}
	}
	return true;
}
bool VirtualFolder::DeleteVirtualFile(std::list<std::string> subfiles,int s)
{	
	if (m_name == subfiles.back())
	{
		auto tmpfile = subfiles.front();
		subfiles.pop_front();
		auto p = GetVirtualPoint(subfiles);
		if (!p)
		{
			printf("ɾ��·��������\n");
			return false;
		}
		p->DeleteVirtualFile(tmpfile,s);
	}
	return true;
}
bool VirtualFolder::DeleteVirtualFile(std::string fileName, int s)
{
	std::list<std::string> allchidren;
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		allchidren.push_back(it->first);
		if (s & 0x1)
		{
			if (it->second->IsPath() && !it->second->IsPathEmpty())
				it->second->DeleteVirtualFile(fileName, s);
		}
	}
	PathUtil::FindWildcard(allchidren, fileName);
	for (auto it = allchidren.begin(); it != allchidren.end(); it++)
	{
		if (!m_vfChildren[*it]->IsPath())
		{
			delete m_vfChildren[*it];
			m_vfChildren.erase(*it);
		}
		else
			continue;
	}
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
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("����·��������\n");
		return false;
	}
	if (p->IsPath())
		return true;
	else
		return false;
}
bool VirtualFolder::FindFile(std::list<std::string> subfiles)
{
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("�ļ�·��������\n");
		return false;
	}
	if (!p->IsPath())
		return true;
	else
	{
		return false;
	}

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
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		auto dstfileName = subfiles.front();
		subfiles.pop_front();
		auto fatherPath = subfiles.front();
		printf("�����ļ�%s�ĸ�·��%s������\n", dstfileName.c_str(), fatherPath.c_str());
		return false;
	}
	if (p->IsPath())
	{
		p->CreateVirtualFile(mem, fsize, dstName);
		return true;
	}
	else
	{
		printf("·���Ƿ�\n");
		return false;
	}
}
bool VirtualFolder::CreateVirtualFile(void *mem, int fsize, const char* dstName)
{
	if (m_vfChildren.find(dstName) != m_vfChildren.end())
		return false;
	auto vf = new VirtualFile();
	vf->SetMemory(mem,fsize);
	m_vfChildren[dstName] = vf;
	m_vfChildren[dstName]->SetName(dstName);
	m_vfChildren[dstName]->Init(this);
	return true;
}
bool VirtualFolder::GetAllFile(std::list<std::string>paths, std::list<std::string>& files)
{
	auto p = GetVirtualPoint(paths);
	if (!p)
	{
		printf("·��������\n");
		return false;
	}
	else
	{
		return p->GetAllFile(files);
	}
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
	auto p = GetVirtualPoint(srcPaths);
	if (!p)
	{
		printf("·��������\n");
		return false;
	}
	p->GetFileMem(mem, size);
	return true;
}
bool VirtualFolder::RenamePathFile(const char* name, std::list<std::string>subfiles)
{
	auto p = GetVirtualPoint(subfiles);
	if (!p)
	{
		printf("������·���ļ�������\n");
		return false;
	}
	else
	{
		p->GetParent()->SetName(subfiles.front().c_str(), name);
		p->SetName(name);
		return true;
	}
}
void VirtualFolder::SetName(const char* oldChildName, const char* newChildName)
{
	if (m_vfChildren.find(oldChildName) != m_vfChildren.end())
	{
		if (m_vfChildren.find(newChildName) != m_vfChildren.end())
		{
			printf("����������%s�Ѵ���\n",newChildName);
			return;
		}
		else
		{
			m_vfChildren[newChildName] = m_vfChildren[oldChildName];
			m_vfChildren[newChildName]->SetName(newChildName);
			m_vfChildren.erase(oldChildName);
		}
	}
}
bool VirtualFolder::SetCursor(std::list<std::string>subfiles)
{
	if (!FindPath(subfiles))
		return false;
	else
		ClearCursor();
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
		printf("·��������\n");
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
		{
			return nullptr;
		}
	}
	else
	{
		printf("���ֲ�ƥ��\n");
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
		printPath =  *it + "\\" + printPath;
	}
	printf("\nv:\\%s��Ŀ¼\n\n", printPath.c_str());
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
	printf("               %d ���ļ�%19d �ֽ�\n", fileNum, allfileSize);
	printf("               %d ��Ŀ¼%19s �����ֽ�\n", fileNum, ullstr.c_str());
	for (auto it = subDirs.begin(); it != subDirs.end(); it++)
	{
		(*it)->PrintMessage(subfiles,state);
	}
}
bool VirtualFolder::MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root)
{
	if (dst.size() == 0)
	{
		printf("·��Ϊ��\n");
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
				printf("·���Ѵ���\n");
				return false;
			}
			m_vfChildren[tmp]->MkLink(src,dst, root);
		}
		else
		{
			auto link = new VirtualMKLink();
			link->Init(src, root);
			m_vfChildren[tmp] = link;
			m_vfChildren[tmp]->SetName(tmp.c_str());
			m_vfChildren[tmp]->Init(this);
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
		printf("�ƶ�Դ·��������\n");
		return;
	}
	auto pdst = GetVirtualPoint(dst);
	if (!pdst)
	{
		printf("�ƶ�Ŀ��·��������\n");
		return;
	}
	src.pop_front();
	auto psrcparent = psrc->GetParent();
	if (!psrcparent)
	{
		printf("�����ƶ����̸�Ŀ¼\n");
	}
	pdst->CopyForMove(psrc, state);
	if (!psrc->GetChildrenSize())
	{
		psrcparent->EraseChild(psrc->GetName());
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
void VirtualFolder::Serialize(const char* dst)
{
	std::ofstream dstfile(dst);
	dstfile << VIRTUALDISK_HEAD;
	char head[128];
	dstfile << head;
	//dstfile.open(dst, std::ios::binary | std::ios::in, 0);
	Encode(dstfile);
	dstfile.close();
}
void VirtualFolder::Encode(std::ofstream& of)
{
	if (!m_broot)
	{
		of << m_type << GetParent()->GetName() << m_name;
	}
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		//it->second->Encode(of);
		//StringUtil::EncodeString(of,it->first);
	}
	/*std::map<std::string, VirtualBlock*>::const_iterator it = m_vfChildren.begin();
	for (; it != m_vfChildren.end(); ++it)
	{
		of << it->first << it->second->type << it->second->Encode(of);
	}*/


}
void VirtualFolder::DeSerialize(const char* src)
{
	std::ifstream srcfile(src);
	//char head[12];
	std::string headName;
	srcfile >> headName;
	if (headName != VIRTUALDISK_HEAD)
	{
		return;
	}
	char head[128];
	srcfile >> head;
	Decode(srcfile);
	srcfile.close();
}
void VirtualFolder::Decode(std::ifstream& inf)
{
	/*{
		std::string file_name;
		int file_type = 0;
		inf >> file_name >> file_type;

		switch (file_type)
		{
		case NORMAL_FILE:
			new
		default:
			break;
		}	*/

}