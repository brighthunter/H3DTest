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
}

void VirtualDiskManager::RegisterCallback()
{
	Functor1wRet<const char*, bool> func_createPath = functor_ret(*this, &VirtualDiskManager::createPath);
	Functor2wRet<const char*, bool,bool>	func_deletePath = functor(*this, &VirtualDiskManager::deletePath);
	Functor2wRet<std::string, std::string, bool>	func_copyPath = functor(*this, &VirtualDiskManager::copyPath);
	Functor1<const char*> func_AddCursor = functor(*this, &VirtualDiskManager::AddCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_CreatePath(func_createPath);
	VirtualDiskManagerObserver::GetInstance()->Register_AddCursor(func_AddCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_DeletePath(func_deletePath);
	VirtualDiskManagerObserver::GetInstance()->Register_CopyPath(func_copyPath);
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
	
	cursor += ">";
	printf(cursor.c_str());
}
void VirtualDiskManager::GetCursor(std::string& cursor)
{
	std::string _cursor;
	_cursor += m_sdiskName + '/';
	
	cursor = _cursor;
}
void VirtualDiskManager::GetCursorWithoutRoot(std::string& cursor)
{
	std::string _cursor;
	
	cursor = _cursor;
}
void VirtualDiskManager::AddCursor(const char* userInput)
{

}
void VirtualDiskManager::ClearCursor()
{
	// root->ClearCursour();
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
	std::list<std::string> subfiles;
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
	std::list<std::string> subfiles;
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
	if (src[0] != '@' && dst[0] != '@')
	{
		return CopyVirtualToVirtual(src, dst);
	}
	else if (src[0] != '@' && dst[0] == '@')
	{
		dst.erase(0, 1);
		return CopyVirtualToRealDisk(src, dst);
	}
	else if (src[0] == '@' && dst[0] != '@')
	{
		src.erase(0, 1);
		return CopyRealDiskToVirtual(src, dst);
	}
	else if (src[0] == '@' && dst[0] == '@')
	{
		src.erase(0, 1);
		dst.erase(0, 1);
		return CopyRealDiskToVirtual(src, dst);
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
bool VirtualDiskManager::getFullPathWithoutRoot(std::string &fullpath, const char* userInput)
{
	std::string slashPath = userInput;
	PathUtil::BackslashToslash(slashPath);
	GetCursorWithoutRoot(fullpath);
	fullpath += userInput;
	return true;
}
bool VirtualDiskManager::CopyRealDiskToRealDisk(std::string src, std::string dst)
{
	if (!PathIsDirectory(dst.c_str()))
	{
		printf("不存在磁盘空间\n");
		return false;
	}
	std::list < std::string > realFiles;
	PathUtil::BackslashToslash(src);
	/*if (PathIsDirectory(src.c_str()))
	{
		PathUtil::GetAllDirAndFiles(src, realFiles);
		for (auto it = realFiles.begin(); it != realFiles.end(); it++)
		{
			if (PathIsDirectory((*it).c_str()))
			{
				std::list < std::string > _paths;
			}
			else
			{
				FILE* _file;
				fopen_s(&_file, (*it).c_str(), "rb");
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				fread_s(mem, fsize, fsize, 1, _file);
				fclose(_file);
				free(mem);
			}

		}
	}
	else
	{
		auto fileName = PathUtil::GetFileName(src);
		auto filePath = PathUtil::GetPath(src);
		if (PathIsDirectory(filePath.c_str()))
		{
			PathUtil::GetAllFiles(filePath, realFiles);
			for (auto it = realFiles.begin(); it != realFiles.end(); it++)
			{
				*it = PathUtil::GetFileName(*it);
			}
			PathUtil::FindWildcard(realFiles, fileName);
			if (realFiles.size() == 0)
			{
				printf("未找到需拷贝路径\n");
			}
			for (auto it = realFiles.begin(); it != realFiles.end(); it++)
			{
				auto tmp = filePath + *it;
				FILE* _file;				
				fopen_s(&_file, tmp.c_str(), "rb");
				if (!_file)
				{
					printf("%s 不存在\n", (*it).c_str());
					return false;
				}
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				fread_s(mem, fsize, fsize, 1, _file);
				fclose(_file);
				fopen_s(&_file, tmp.c_str(), "wb");
				fwrite()
				free(mem);

			}

		}
		else
		{
			printf("预拷贝路径不存在\n");
			return false;
		}
	}*/
	return true;
}
bool VirtualDiskManager::CopyVirtualToVirtual(std::string src, std::string dst)
{
	std::list < std::string > dstPaths;
	PathUtil::BackslashToslash(dst);
	std::string fulldstPath;
	getFullPathWithoutRoot(fulldstPath,dst.c_str());
	PathUtil::SeperateFile(fulldstPath, dstPaths);
	if (!root->FindPath(dstPaths))
	{
		printf("虚拟磁盘目的路径不存在\n");
		return false;
	}
	//src
	std::list < std::string > srcPaths;
	std::string fullsrcPath;
	getFullPathWithoutRoot(fullsrcPath, src.c_str());
	PathUtil::BackslashToslash(fullsrcPath);
	PathUtil::SeperateFile(fullsrcPath, srcPaths);
	std::string srcPath;
	std::string srcFile;
	if (!root->FindPath(srcPaths))
	{
		srcPaths.clear();
		srcPath = PathUtil::GetPath(fullsrcPath);	
		srcFile = PathUtil::GetFileName(fullsrcPath);
		PathUtil::SeperateFile(srcPath, srcPaths);
		if (!root->FindPath(srcPaths))
		{
			printf("虚拟磁盘源路径不存在\n");
			return false;
		}

	}
	else
	{
		srcPath = fullsrcPath;
	}	
	std::list < std::string > srcFiles;
	root->GetAllFile(srcPaths, srcFiles);
	if(srcFile !=  "")
		PathUtil::FindWildcard(srcFiles, srcFile);
	for (auto it = srcFiles.begin(); it != srcFiles.end(); it++)
	{
		std::list < std::string > tmpPaths;
		
		srcPaths.push_front(*it);
		void** mem = new void*();
		*mem = nullptr;
		int size = 0;
		root->GetFileMem(srcPaths,mem,size);
		if (mem != nullptr && size != 0)
		{
			root->CreateVirtualFile(*mem,size,dstPaths,(*it).c_str());
		}
		delete mem;
		srcPaths.pop_front();
	}
	return true;
}

bool VirtualDiskManager::CopyVirtualToRealDisk(std::string src, std::string dst)
{
	if (!PathIsDirectory(dst.c_str()))
	{
		printf("目标磁盘路径不存在或不是路径\n");
		return false;
	}
	dst += '/';
	//src
	std::list < std::string > srcPaths;
	std::string fullsrcPath;
	getFullPathWithoutRoot(fullsrcPath, src.c_str());
	PathUtil::BackslashToslash(fullsrcPath);
	PathUtil::SeperateFile(fullsrcPath, srcPaths);
	std::string srcPath;
	std::string srcFile;
	if (!root->FindPath(srcPaths))
	{
		srcPaths.clear();
		srcPath = PathUtil::GetPath(fullsrcPath);
		srcFile = PathUtil::GetFileName(fullsrcPath);
		PathUtil::SeperateFile(srcPath, srcPaths);
		if (!root->FindPath(srcPaths))
		{
			printf("虚拟磁盘源路径不存在\n");
			return false;
		}

	}
	else
	{
		srcPath = fullsrcPath;
	}

	std::list < std::string > srcFiles;
	root->GetAllFile(srcPaths, srcFiles);
	if (srcFile != "")
		PathUtil::FindWildcard(srcFiles, srcFile);
	for (auto it = srcFiles.begin(); it != srcFiles.end(); it++)
	{
		std::list < std::string > tmpPaths;

		srcPaths.push_front(*it);
		void** mem = new void*();
		*mem = nullptr;
		int size = 0;
		root->GetFileMem(srcPaths, mem, size);
		if (mem != nullptr && size != 0)
		{
			auto tmp = dst + *it;
			FILE* _file;
			fopen_s(&_file,tmp.c_str(), "wb");
			fwrite(*mem, size, 1, _file);
			fclose(_file);
		}
		delete mem;
		srcPaths.pop_front();
	}
	return true;
}
bool VirtualDiskManager::CopyRealDiskToVirtual(std::string src, std::string dst)
{
	//dst
	std::list < std::string > dstFiles;
	PathUtil::BackslashToslash(dst);
	PathUtil::SeperateFile(dst, dstFiles);
	if (!root->FindPath(dstFiles))
	{
		printf("虚拟磁盘目的路径不存在\n");
		return false;
	}
	//src
	std::list < std::string > realFiles;
	PathUtil::BackslashToslash(src);
	if (PathIsDirectory(src.c_str()))
	{	
		PathUtil::GetAllDirAndFiles(src, realFiles);
		for (auto it = realFiles.begin(); it != realFiles.end(); it++)
		{
			if (PathIsDirectory((*it).c_str()))
			{
				std::list < std::string > _paths;
				root->createPath(_paths);
			}
			else
			{
				FILE* _file;
				fopen_s(&_file,(*it).c_str(), "rb");
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				fseek(_file, 0, SEEK_SET);
				fread_s(mem, fsize,fsize,1,_file);
				root->CreateVirtualFile(mem, fsize, dstFiles, (*it).c_str());
				free(mem);
				fclose(_file);
			}

		}
	}
	else
	{
		auto fileName = PathUtil::GetFileName(src);
		auto filePath = PathUtil::GetPath(src);
		if (PathIsDirectory(filePath.c_str()))
		{
			PathUtil::GetAllFiles(filePath, realFiles);
			for (auto it = realFiles.begin(); it != realFiles.end(); it++)
			{
				*it = PathUtil::GetFileName(*it);
			}
			PathUtil::FindWildcard(realFiles, fileName);
			if (realFiles.size() == 0)
			{
				printf("未找到需拷贝路径\n");
			}
			for (auto it = realFiles.begin(); it != realFiles.end(); it++)
			{
				auto tmp  = filePath + *it;
				FILE* _file;
				fopen_s(&_file, tmp.c_str(), "rb");
				if (!_file)
				{
					printf("%s 不存在\n", (*it).c_str());
					return false;
				}
				fseek(_file,0,SEEK_END);
				auto fsize = ftell(_file);
				fseek(_file, 0, SEEK_SET);
				void* mem = malloc(fsize);
				fread_s(mem, fsize, 1, fsize, _file);
				root->CreateVirtualFile(mem,fsize, dstFiles, (*it).c_str());
				free(mem);
			}
			
		}
		else
		{
			printf("预拷贝路径不存在\n");
			return false;
		}
	}
	return true;
		
}
void VirtualDiskManager::Rename(const char* userInput, const char* name)
{
	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::list < std::string > virtualFiles;
	PathUtil::SeperatePath(fullpath, virtualFiles);
	/*if(root->FindPath(virtualFiles))
		root->RenamePath(virtualFiles, name);
	else
	{

	}*/
}
