#include "VirtualMKLink.h"
VirtualMKLink::VirtualMKLink()
{
}

VirtualMKLink::~VirtualMKLink()
{
}
bool VirtualMKLink::createPath(std::list<std::string> subfiles)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	p->createPath(subfiles);
	return true;
}
bool VirtualMKLink::deletePath(std::list<std::string> subfiles, int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	p->deletePath(subfiles,s);
	return true;
}
bool VirtualMKLink::DeleteVirtualFile(std::list<std::string> subfiles, int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	p->DeleteVirtualFile(subfiles,s);
	return true;
}
bool VirtualMKLink::DeleteVirtualFile(int s)
{
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return false;
	}
	p->DeleteVirtualFile(s);
	return true;
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
bool VirtualMKLink::Init()
{
	return true;
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
	auto p = m_root->GetVirtualPoint(m_paths);
	if (!p)
	{
		printf("符号链接不存在\n");
		return nullptr;
	}
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