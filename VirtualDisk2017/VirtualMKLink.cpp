#include "VirtualMKLink.h"
VirtualMKLink::VirtualMKLink()
{
}

VirtualMKLink::~VirtualMKLink()
{
}
std::string VirtualMKLink::GetDir(bool linkCursor)
{
	if (!m_bCursor || !m_isPath)
		return "";
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	std::string cursor;
	cursor = m_name + '\\' + p->GetDir(true);
	return cursor;
}
bool VirtualMKLink::CreateVirtualPath(std::list<std::string> subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->CreateVirtualPath(subfiles);
}
bool VirtualMKLink::DeleteVirtualPath(std::list<std::string> subfiles, int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->DeleteVirtualPath(subfiles,s);
}
bool VirtualMKLink::DeleteVirtualPath(std::string fileName , int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->DeleteVirtualPath(fileName, s);
}
bool VirtualMKLink::DeleteVirtualFile(std::list<std::string> subfiles, int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->DeleteVirtualFile(subfiles,s);
}
bool VirtualMKLink::DeleteVirtualFile(std::string fileName,int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->DeleteVirtualFile(fileName,s);
}
bool VirtualMKLink::IsPathEmpty()
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->IsPathEmpty();
}

bool VirtualMKLink::IsRoot()
{
	return false;
}
bool VirtualMKLink::FindPath(std::list<std::string> subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->FindPath(subfiles);
}
bool VirtualMKLink::FindPathFile(std::list<std::string> subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->FindPathFile(subfiles);
}
bool VirtualMKLink::CreateVirtualFile(void *mem, int fsize, const char* dstName)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->CreateVirtualFile(mem, fsize, dstName);
}

bool VirtualMKLink::Init(std::list<std::string> linkPath, VirtualBlock* root)
{
	m_paths = linkPath;
	m_root = root;
	auto p = root->GetVirtualPoint(linkPath);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	m_isPath = root->GetVirtualPoint(linkPath)->IsPath();
	return true;
}
bool VirtualMKLink::GetAllFile(std::list<std::string>paths, std::list<std::string>& files)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->GetAllFile(paths, files);
}
bool VirtualMKLink::GetAllFile(std::list<std::string>& files)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->GetAllFile(files);
}
bool VirtualMKLink::GetFileMem(std::list<std::string> srcPaths, void** mem, int& size)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->GetFileMem(srcPaths, mem, size);

}
bool VirtualMKLink::GetFileMem(void** mem, int& size)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->GetFileMem(mem, size);
}
int  VirtualMKLink::VirtualMKLink::GetFileSzie()
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->GetFileSzie();
}
bool VirtualMKLink::RenamePathFile(const char* name, std::list<std::string>subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->RenamePathFile(name, subfiles);
}
bool VirtualMKLink::SetCursor(std::list<std::string>subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->SetCursor(subfiles);
}
bool VirtualMKLink::SetCursor()
{
	m_bCursor = true;
	return true;
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->SetCursor();
}
bool VirtualMKLink::ClearCursor()
{
	m_bCursor = false;
	return true;
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->ClearCursor();
}
void VirtualMKLink::PrintPathMessage(bool hasName)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	printf("%s  %s    <SYMLINKD>     %s [%s]\n", m_datetime, m_daytime, m_name.c_str(),p->GetName().c_str());
	return p->PrintPathMessage(hasName);

}
void VirtualMKLink::PrintMessage(std::list<std::string> subfiles, int state)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->PrintMessage(subfiles,state);
}
VirtualBlock* VirtualMKLink::GetVirtualPoint(std::list<std::string>subfiles)
{
	if (subfiles.size() == 1)
	{
		if (subfiles.back() == m_name)
			return this;
	}
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return nullptr;
	}
	subfiles.pop_back();
	subfiles.push_back(p->GetName());
	return p->GetVirtualPoint(subfiles);
}
bool VirtualMKLink::MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	return p->MkLink(src,dst,root);
}
void VirtualMKLink::Save(std::string dst)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->Save(dst);
}
void VirtualMKLink::Clear()
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->Clear();
}
void VirtualMKLink::EraseChild(std::string cname)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->EraseChild(cname);
}
void VirtualMKLink::CopyForMove(VirtualBlock* pchild, int state)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->CopyForMove(pchild, state);
}
void VirtualMKLink::Combine(VirtualBlock*pchild, int state)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return;
	}
	return p->Combine(pchild, state);

}
int VirtualMKLink::GetChildrenSize() 
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return 0;
	}
	return p->GetChildrenSize();
}
void VirtualMKLink::SetName(const char* oldChildName, const char* newChildName)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return ;
	}
	return p->SetName(oldChildName,newChildName);
}