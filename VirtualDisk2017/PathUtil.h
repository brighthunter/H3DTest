#ifndef _PathUtil_H_
#define _PathUtil_H_
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
namespace PathUtil
{
	static void SeperatePath(std::string Allpath,std::vector<std::string>& subpaths)
	{
		while (Allpath.find_last_of(" ")!= -1)
		{
			int num = Allpath.find_last_of(" ");
			if (num != Allpath.size())
			{
				std::string subpath = Allpath.substr(num + 1, Allpath.size());
				subpaths.push_back(subpath);
				Allpath.erase(num, Allpath.size());
			}
			else
			{
				Allpath.pop_back();
			}
		}
		if(Allpath != "")
			subpaths.push_back(Allpath);
	}
	static void BackslashToslash(std::string& path)
	{
		while (path.find_first_of("\\") != -1)
		{
			path[path.find_first_of("\\")] = '/';
		}
	}
	static void SeperateFile(std::string path, std::vector<std::string>& subfiles)
	{
		while (path.find_last_of("/") != -1)
		{
			int num = path.find_last_of("/");
			if (num != path.size())
			{
				std::string subfile = path.substr(num + 1, path.size());
				subfiles.push_back(subfile);
				path.erase(num, path.size());
			}
			else
			{
				path.pop_back();
			}
		}
		if (path != "")
			subfiles.push_back(path);
		for (auto it = subfiles.end(); it != subfiles.begin(); )
		{
			--it;			
			if (*it == "..")
			{
				it = subfiles.erase(it);
				it = subfiles.erase(it);
			}

		}
	}
	static void GetAllFiles(std::string path, std::vector<std::string>& files)
	{
		//文件句柄
		long hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		std::string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
		if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) 
		{
			    do {
				        if (fileinfo.attrib & _A_SUBDIR)
						{  //比较文件类型是否是文件夹
					            if ((strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0))
								{
						            files.push_back(p.assign(path).append("/").append(fileinfo.name));
									GetAllFiles(p.assign(path).append("/").append(fileinfo.name), files);
								}			
						}
						else {
					            files.push_back(p.assign(path).append("/").append(fileinfo.name));
						}
				
					} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
				 _findclose(hFile);
		}
	}
	static void GetDirFiles(std::string path, std::vector<std::string>& files)
	{
		//文件句柄
		long hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;  //很少用的文件信息读取结构
		std::string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
		if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
		{
			do {
				if (fileinfo.attrib & _A_SUBDIR)
				{  //比较文件类型是否是文件夹
					continue;
				}
				else {
					files.push_back(p.assign(path).append("/").append(fileinfo.name));
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	static std::string GetPath(std::string path)
	{
		std::string fileName;
		if (path.find_last_of("/") != -1)
		{
			int num = path.find_last_of("/");
			if (num != path.size())
			{
				fileName = path.substr(num);
			}
		}
		return fileName;
	}
	static std::string GetFileName(std::string path)
	{
		std::string fileName;
		if (path.find_last_of("/") != -1)
		{
			int num = path.find_last_of("/");
			if (num != path.size())
			{
				fileName = path.substr(num + 1, path.size());	
			}
		}
		return fileName;
	}
}
#endif