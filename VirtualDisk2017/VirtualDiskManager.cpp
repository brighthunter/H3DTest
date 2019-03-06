#include "VirtualDiskManager.h"
#include "Tool/functor.h"
#include "PathUtil.h"
#include "VirtualDiskManagerObserver.h"
#include <Shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
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
	Functor1wRet<const char*, bool> func_createPath = functor_ret(*this, &VirtualDiskManager::createPath);
	Functor2wRet<const char*, bool,bool>	func_deletePath = functor(*this, &VirtualDiskManager::deletePath);
	Functor1<VirtualFolder*> func_AddCursor = functor(*this, &VirtualDiskManager::AddCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_CreatePath(func_createPath);
	VirtualDiskManagerObserver::GetInstance()->Register_AddCursor(func_AddCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_DeletePath(func_deletePath);
}
bool VirtualDiskManager::Init()
{
	bool res = true;
	m_pCommondmanager = new CommondManager();
	res &= m_pCommondmanager->Init();
	m_sdiskName = "v:";
	RegisterCallback();
	root = new VirtualFolder();
	return res;
}
void VirtualDiskManager::PrintCursor()
{
	std::string cursor;
	cursor += m_sdiskName + '\\';
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{		
		cursor += it->second->GetDir();	
	}
	cursor += ">";
	printf(cursor.c_str());
}
void VirtualDiskManager::GetCursor(std::string& cursor)
{
	std::string _cursor;
	_cursor += m_sdiskName + '/';
	for (auto it = m_vfChildren.begin(); it != m_vfChildren.end(); it++)
	{
		_cursor += it->second->GetDir();
	}
	cursor = _cursor;
}
void VirtualDiskManager::AddCursor(VirtualFolder* pvf)
{
	m_pvfCursorlist.push_back(pvf);
}
void VirtualDiskManager::ClearCursor()
{
	m_pvfCursorlist.clear();
}
bool VirtualDiskManager::analyzeCommond(const char* userInput)
{
	if (!m_pCommondmanager)
		return false;
	std::string Input;
	return m_pCommondmanager->analyzeCommond(userInput);
	
}
bool VirtualDiskManager::createPath(const char* userInput)
{

	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::vector<std::string> subfiles;
	PathUtil::SeperateFile(fullpath, subfiles);
	auto tmp = *subfiles.begin();
	subfiles.pop_back();
	if (!subfiles.size())
	{
		return true;
	}
	return root->createPath(subfiles);
}
bool VirtualDiskManager::deletePath(const char* userInput,bool s)
{
	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::vector<std::string> subfiles;
	PathUtil::SeperateFile(fullpath, subfiles);
	auto tmp = *subfiles.begin();
	subfiles.pop_back();
	if (!subfiles.size())
	{
		return true;
	}
	return root->deletePath(subfiles,s);
}
bool VirtualDiskManager::copyPath(std::string src, std::string dst)
{
	if (!src.size() || !dst.size())
	{
		printf("目标或拷贝文件为空\n");
		return true;
	}
	if (dst[0] == '@')
	{
		printf("不支持向磁盘中拷贝\n");
	}
	if (src[0] == '@')
	{
		CopyRealDiskToPath(src, dst);
	}
	else
	{
		//CopyVirtualToPath(src, dst);
	}
	return false;

}
bool VirtualDiskManager::getFullPath(std::string &fullpath,const char* userInput)
{
	std::string slashPath = userInput;
	PathUtil::BackslashToslash(slashPath);
	GetCursor(fullpath);
	fullpath += userInput;	
	return true;
}
void VirtualDiskManager::CopyRealDiskToPath(std::string src, std::string dst)
{
	std::vector < std::string > virtualFiles;
	PathUtil::SeperatePath(dst, virtualFiles);
	if (!root->FindPath(virtualFiles))
	{
		printf("虚拟磁盘路径不存在\n");
		return;
	}
	src.erase(src.front());
	std::vector < std::string > realFiles;
	if (PathIsDirectory(src.c_str()))
	{	
		PathUtil::GetAllFiles(src, realFiles);
		for (auto it = realFiles.begin(); it != realFiles.end(); it++)
		{
			FILE* _file;
			fopen_s(&_file,(*it).c_str(), "rb");
			auto fsize = ftell(_file);
			void* mem = malloc(fsize);
			fread_s(mem, fsize,fsize,1,_file);
			root->CreateVirtualFile(mem, fsize, virtualFiles, (*it).c_str());
			free(mem);

		}
	}
	else
	{
		auto fileName = PathUtil::GetFileName(src);
		auto filePath = PathUtil::GetPath(src);

	}
	
		
}
void VirtualDiskManager::Rename(const char* userInput, const char* name)
{
	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::vector < std::string > virtualFiles;
	PathUtil::SeperatePath(fullpath, virtualFiles);
	/*if(root->FindPath(virtualFiles))
		root->RenamePath(virtualFiles, name);
	else
	{

	}*/
}