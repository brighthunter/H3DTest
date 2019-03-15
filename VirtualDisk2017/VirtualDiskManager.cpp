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
	Functor1wRet<const char*, bool> func_createPath = functor_ret(*this, &VirtualDiskManager::CreateVirtualPath);
	Functor2wRet<const char*, bool,bool>	func_deletePath = functor(*this, &VirtualDiskManager::DeleteVirtualPath);
	Functor2wRet<std::string, std::string, bool>	func_copyPath = functor(*this, &VirtualDiskManager::copyPath);
	Functor2<const char*, const char*>    func_rename = functor(*this, &VirtualDiskManager::Rename);
	Functor1<const char*> func_AddCursor = functor(*this, &VirtualDiskManager::AddCursor);
	Functor1<const char*> func_setCursor = functor(*this, &VirtualDiskManager::SetCursor);
	Functor2<const char*,int> func_delteeVirtualFile = functor(*this, &VirtualDiskManager::DeleteVirtualFile);
	Functor2<const char*,int> func_printDir = functor(*this, &VirtualDiskManager::PrintDir);
	Functor2<const char*, const char*> func_mklink = functor(*this, &VirtualDiskManager::MkLink);
	Functor1<const char*> func_save = functor(*this, &VirtualDiskManager::Save);
	Functor1<const char*> func_load = functor(*this, &VirtualDiskManager::Load);
	Functor1<const char*> func_saf = functor(*this, &VirtualDiskManager::Saf);
	Functor1<const char*> func_lod = functor(*this, &VirtualDiskManager::Lod);
	Functor3<const char*,const char*,int> func_move = functor(*this, &VirtualDiskManager::Move);
	VirtualDiskManagerObserver::GetInstance()->Register_CreatePath(func_createPath);
	VirtualDiskManagerObserver::GetInstance()->Register_AddCursor(func_AddCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_DeletePath(func_deletePath);
	VirtualDiskManagerObserver::GetInstance()->Register_CopyPath(func_copyPath);
	VirtualDiskManagerObserver::GetInstance()->Register_Rename(func_rename);
	VirtualDiskManagerObserver::GetInstance()->Register_SetCursor(func_setCursor);
	VirtualDiskManagerObserver::GetInstance()->Register_DeleteVirtualFile(func_delteeVirtualFile);
	VirtualDiskManagerObserver::GetInstance()->Register_PrintDir(func_printDir);
	VirtualDiskManagerObserver::GetInstance()->Register_Mklink(func_mklink);
	VirtualDiskManagerObserver::GetInstance()->Register_Save(func_save);
	VirtualDiskManagerObserver::GetInstance()->Register_Load(func_load);
	VirtualDiskManagerObserver::GetInstance()->Register_Move(func_move);
	VirtualDiskManagerObserver::GetInstance()->Register_Saf(func_saf);
	VirtualDiskManagerObserver::GetInstance()->Register_Lod(func_lod);
}
bool VirtualDiskManager::Init()
{
	bool res = true;
	m_pCommondmanager = new CommondManager();
	if (!m_pCommondmanager)
	{
		printf("m_pCommondmanager创建失败\n");
		return false;
	}
	res &= m_pCommondmanager->Init();
	m_sdiskName = "v:";
	RegisterCallback();
	m_root = new VirtualFolder();
	if (!m_root)
	{
		printf("Root创建失败\n");
		return false;
	}
	m_root->SetName("v:");
	m_root->SetRoot(true);
	return res;
}
void VirtualDiskManager::PrintCursor()
{
	std::string cursor;
	//cursor += m_sdiskName + '\\';
	cursor += m_root->GetDir();
	cursor += ">";
	printf(cursor.c_str());
}
void VirtualDiskManager::GetCursor(std::string& cursor)
{
	std::string _cursor;
	//_cursor += m_sdiskName + '/';
	_cursor += m_root->GetDir();
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
void VirtualDiskManager::PrintDir(const char* userInput,int state)
{
	std::string fullPathfile;
	getFullPath(fullPathfile, userInput);
	std::list<std::string> subfiles;
	PathUtil::SeperateFile(fullPathfile, subfiles);
	m_root->PrintDir(subfiles, state);
	
}
bool VirtualDiskManager::analyzeCommond(const char* userInput)
{
	if (!m_pCommondmanager)
		return false;
	std::string Input;
	return m_pCommondmanager->analyzeCommond(userInput);
	
}
bool VirtualDiskManager::CreateVirtualPath(const char* userInput)
{

	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::list<std::string> subfiles;
	PathUtil::BackslashToslash(fullpath);
	PathUtil::SeperateFile(fullpath, subfiles);
	return m_root->CreateVirtualPath(subfiles);
}
bool VirtualDiskManager::DeleteVirtualPath(const char* userInput,bool s)
{
	std::string fullpath;
	getFullPath(fullpath, userInput);
	std::list<std::string> subfiles;
	PathUtil::SeperateFile(fullpath, subfiles);
	if (!subfiles.size())
	{
		return true;
	}
	return m_root->DeleteVirtualPath(subfiles,s);
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
	if (slashPath.find("v:/") != 0)
	{
		GetCursor(fullpath);
		PathUtil::BackslashToslash(fullpath);
	}
	fullpath += userInput;	
	return true;
}
bool VirtualDiskManager::getFullPathWithoutRoot(std::string &fullpath, const char* userInput)
{
	std::string slashPath = userInput;
	PathUtil::BackslashToslash(slashPath);
	if (slashPath.find("v:/") == 0)
	{
		fullpath = userInput;
		return true;
	}
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
	if (PathIsDirectory(src.c_str()))
	{
		PathUtil::GetAllDirAndFiles(src, realFiles);
		for (auto it = realFiles.begin(); it != realFiles.end(); it++)
		{
			if (PathIsDirectory((*it).c_str()))
			{
			}
			else
			{
				FILE* _file;
				fopen_s(&_file, (*it).c_str(), "rb");
				if (!_file)
					continue;
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				if (!mem)
				{
					fclose(_file);
					continue;
				}
				fread_s(mem, fsize, fsize, 1, _file);
				fclose(_file);
				fopen_s(&_file, (*it).c_str(), "wb");
				if (!_file)
					continue;
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
					continue;
				}
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				if (!mem)
				{
					fclose(_file);
					continue;
				}
				fread_s(mem, fsize, fsize, 1, _file);
				fclose(_file);
				fopen_s(&_file, tmp.c_str(), "wb");
				if (!_file)
				{
					free(mem);
					continue;
				}
				fwrite(mem, fsize, 1, _file);
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
bool VirtualDiskManager::CopyVirtualToVirtual(std::string src, std::string dst)
{
	std::list < std::string > dstPaths;
	PathUtil::BackslashToslash(dst);
	std::string fulldstPath;
	getFullPath(fulldstPath,dst.c_str());
	PathUtil::SeperateFile(fulldstPath, dstPaths);
	if (!m_root->FindPath(dstPaths))
	{
		printf("虚拟磁盘目的路径不存在\n");
		return false;
	}
	//src
	std::list < std::string > srcPaths;
	std::string fullsrcPath;
	getFullPath(fullsrcPath, src.c_str());
	PathUtil::BackslashToslash(fullsrcPath);
	PathUtil::SeperateFile(fullsrcPath, srcPaths);
	std::string srcPath;
	std::string srcFile;
	if (!m_root->FindPath(srcPaths))
	{
		srcPaths.clear();
		srcPath = PathUtil::GetPath(fullsrcPath);	
		srcFile = PathUtil::GetFileName(fullsrcPath);
		PathUtil::SeperateFile(srcPath, srcPaths);
		if (!m_root->FindPath(srcPaths))
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
	m_root->GetAllFile(srcPaths, srcFiles);
	if(srcFile !=  "")
		PathUtil::FindWildcard(srcFiles, srcFile);
	for (auto it = srcFiles.begin(); it != srcFiles.end(); it++)
	{
		std::list < std::string > tmpPaths;
		
		srcPaths.push_front(*it);
		void** mem = new void*();
		if (!mem)
		{
			printf("mem*指针创建失败\n");
			return false;
		}
		*mem = nullptr;
		int size = 0;
		m_root->GetFileMem(srcPaths,mem,size);
		if (mem != nullptr && size != 0)
		{
			m_root->CreateVirtualFile(*mem,size,dstPaths,(*it).c_str());
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
		printf("目标磁盘路径%s不存在或不是路径\n",dst.c_str());
		return false;
	}
	dst += '/';
	//src
	std::list < std::string > srcPaths;
	std::string fullsrcPath;
	getFullPath(fullsrcPath, src.c_str());
	PathUtil::BackslashToslash(fullsrcPath);
	PathUtil::SeperateFile(fullsrcPath, srcPaths);
	std::string srcPath;
	std::string srcFile;
	if (!m_root->FindPath(srcPaths))
	{
		srcPaths.clear();
		srcPath = PathUtil::GetPath(fullsrcPath);
		srcFile = PathUtil::GetFileName(fullsrcPath);
		PathUtil::SeperateFile(srcPath, srcPaths);
		if (!m_root->FindPath(srcPaths))
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
	m_root->GetAllFile(srcPaths, srcFiles);
	if (srcFile != "")
		PathUtil::FindWildcard(srcFiles, srcFile);
	for (auto it = srcFiles.begin(); it != srcFiles.end(); it++)
	{
		std::list < std::string > tmpPaths;

		srcPaths.push_front(*it);
		void** mem = new void*();
		if (!mem)
		{
			printf("mem*指针创建失败\n");
			return false;
		}
		*mem = nullptr;
		int size = 0;
		m_root->GetFileMem(srcPaths, mem, size);
		if (mem != nullptr && size != 0)
		{
			auto tmp = dst + *it;
			FILE* _file;
			fopen_s(&_file,tmp.c_str(), "wb");
			if (!_file)
			{
				delete mem;
				continue;
			}
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
	std::string fullDst;
	getFullPath(fullDst, dst.c_str());
	PathUtil::BackslashToslash(fullDst);
	PathUtil::SeperateFile(fullDst, dstFiles);
	if (!m_root->FindPath(dstFiles))
	{
		printf("虚拟磁盘目的路径不存在\n");
		return false;
	}
	//src
	std::list < std::string > realFiles;
	PathUtil::BackslashToslash(src);
	if (PathIsDirectory(src.c_str()))
	{	
		PathUtil::GetAllFiles(src, realFiles);
		for (auto it = realFiles.begin(); it != realFiles.end(); it++)
		{
			std::list < std::string > _paths;
			PathUtil::SeperateFile((*it).c_str(), _paths);
			if (PathIsDirectory((*it).c_str()))
			{
				printf("代码错误：%s路径判断错误\n",(*it).c_str());
				continue;
				m_root->CreateVirtualPath(_paths);
			}
			else
			{
				FILE* _file = NULL;
				fopen_s(&_file,(*it).c_str(), "rb");
				if (!_file)
				{
					continue;
				}
				fseek(_file, 0, SEEK_END);
				auto fsize = ftell(_file);
				void* mem = malloc(fsize);
				if (!mem)
				{
					//printf("内存已满\n");
					fclose(_file);
					continue;
					//return false;
				}
				fseek(_file, 0, SEEK_SET);
				fread_s(mem, fsize,fsize,1,_file);
				auto fileName = _paths.front();
				bool b = m_root->CreateVirtualFile(mem, fsize, dstFiles, fileName.c_str());
				free(mem);
				fclose(_file);
				if (!b)
					return false;
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
				if (!mem)
				{
					fclose(_file);
					continue;
				}
				fread_s(mem, fsize, 1, fsize, _file);
				bool b = m_root->CreateVirtualFile(mem,fsize, dstFiles, (*it).c_str());
				free(mem);
				if(!b)
					return false;
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
	PathUtil::SeperateFile(fullpath, virtualFiles);
	m_root->RenamePathFile(name, virtualFiles);
	
}
void VirtualDiskManager::SetCursor(const char* userInput)
{
	std::string fullPath;
	getFullPath(fullPath, userInput);
	std::list<std::string> subfiles;
	PathUtil::SeperateFile(fullPath, subfiles);
	m_root->SetCursor(subfiles);

}
void VirtualDiskManager::DeleteVirtualFile(const char* userInput,int s)
{
	std::string fullPath;
	getFullPath(fullPath, userInput);
	std::list<std::string> subfiles;
	PathUtil::SeperateFile(fullPath, subfiles); 
	m_root->DeleteVirtualFile(subfiles,s);
}
void VirtualDiskManager::MkLink(const char* src, const char* dst)
{
	std::string fullPathsrc;
	getFullPath(fullPathsrc, src);
	std::string fullPathdst;
	getFullPath(fullPathdst, dst);
	std::list<std::string> srcfiles;
	PathUtil::SeperateFile(fullPathsrc, srcfiles);
	std::list<std::string> dstfiles;
	PathUtil::SeperateFile(fullPathdst, dstfiles);
	if (!m_root->GetVirtualPoint(srcfiles))
	{
		printf("不能为不存在的路径创建链接\n");
	}
	m_root->MkLink(srcfiles, dstfiles, m_root);
}
void VirtualDiskManager::Saf(const char* dst)
{
	if (dst[0] != '@')
	{
		printf("请序列化到真实磁盘中\n");
		return;
	}
	std::string realdst = dst;
	realdst.erase(0, 1);
	if (!PathFileExists(realdst.c_str()))
	{
		printf("序列化磁盘路径不存在\n");
		return;
	} 
	
	std::string fullPathdst;
	getFullPath(fullPathdst, realdst.c_str());
	
	std::list<std::string> dstPaths;
	PathUtil::SeperateFile(fullPathdst, dstPaths);
	m_root->Save(realdst.c_str());

}
void VirtualDiskManager::Lod(const char* src)
{
	if (src[0] != '@')
	{
		printf("请从真实磁盘中重建虚拟磁盘文件\n");
		return;
	}
	std::string realsrc = src;
	realsrc.erase(0, 1);
	if (!PathFileExists(realsrc.c_str()))
	{
		printf("真实磁盘路径不存在\n");
		return;
	}
	m_root->Clear();
	std::list<std::string> allFiles;
	PathUtil::GetAllDirAndFiles(realsrc, allFiles);
	for (auto it = allFiles.begin(); it != allFiles.end(); it++)
	{
		std::list<std::string> subfiles;
		auto virtualPath = *it;
		virtualPath.erase(0, realsrc.size() + 1);
		virtualPath = "v:/" + virtualPath;
		PathUtil::SeperateFile(virtualPath, subfiles);
		if (PathIsDirectory((*it).c_str()))
		{
			m_root->CreateVirtualPath(subfiles);
		}
		else
		{
			FILE* _file;
			fopen_s(&_file, (*it).c_str(), "rb");
			if (!_file)
				continue;
			fseek(_file, 0, SEEK_END);
			auto fsize = ftell(_file);
			fseek(_file, 0, SEEK_SET);
			printf("Reading %s Begin\n",(*it).c_str());
			void* mem = malloc(fsize);
			if (!mem)
			{
				fclose(_file);
				continue;
			}
			fread_s(mem, fsize, fsize, 1, _file);
			fclose(_file);
			printf("Reading %s End\n", (*it).c_str());
			auto dstName = subfiles.front();
			subfiles.pop_front();
			auto b = m_root->CreateVirtualFile(mem,fsize, subfiles, dstName.c_str());
			if (!b)
				return;
			free(mem);
		}
	}

	
}
void VirtualDiskManager::Save(const char* dst)
{
	if (dst[0] != '@')
	{
		printf("请序列化到真实磁盘中\n");
		return;
	}
	std::string realdst = dst;
	realdst.erase(0, 1);
	m_root->Serialize(realdst.c_str());
	return;
	
}
void VirtualDiskManager::Load(const char* src)
{
	if (src[0] != '@')
	{
		printf("请从真实磁盘中重建虚拟磁盘文件\n");
		return;
	}	
	m_root->Clear();
	std::string realsrc = src;
	realsrc.erase(0, 1);
	{
		m_root->DeSerialize(realsrc.c_str());
		return;
	}
}
void VirtualDiskManager::Move(const char* src, const char* dst,int state)
{
	if (src[0] == '@' || dst[0] == '@')
	{
		printf("仅支持虚拟磁盘路径\n");
		return;
	}
	std::string fullPathsrc;
	getFullPath(fullPathsrc, src);
	std::string fullPathdst;
	getFullPath(fullPathdst, dst);
	std::list<std::string> srcfiles;
	PathUtil::SeperateFile(fullPathsrc, srcfiles);
	std::list<std::string> dstfiles;
	PathUtil::SeperateFile(fullPathdst, dstfiles);
	m_root->Move(srcfiles, dstfiles, state);
}

void VirtualDiskManager::Serialize(const char* dst)
{
	m_root->Serialize(dst);
}