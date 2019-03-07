#ifndef _PathUtil_H_
#define _PathUtil_H_
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
namespace PathUtil
{
	static void SeperatePath(std::string Allpath, std::list<std::string>& subpaths)
	{
		while (Allpath.find_last_of(" ") != -1)
		{
			int num = Allpath.find_last_of(" ");
			if (num != Allpath.size())
			{
				std::string subpath = Allpath.substr(num + 1, Allpath.size());
				if (subpath != "")
					subpaths.push_back(subpath);
				Allpath.erase(num, Allpath.size());
			}
			else
			{
				Allpath.pop_back();
			}
		}
		if (Allpath != "")
			subpaths.push_back(Allpath);
	}
	static void BackslashToslash(std::string& path)
	{
		while (path.find_first_of("\\") != -1)
		{
			path[path.find_first_of("\\")] = '/';
		}
	}
	static void SeperateFile(std::string path, std::list<std::string>& subfiles)
	{
		while (path.find_last_of("/") != -1)
		{
			int num = path.find_last_of("/");
			if (num != path.size())
			{
				std::string subfile = path.substr(num + 1, path.size());
				if (subfile != "")
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
	static void SeperateStar(std::string fileName, std::list<std::string>& subfiles)
	{
		while (fileName.find_last_of("*") != -1)
		{
			int num = fileName.find_last_of("*");
			if (num != fileName.size())
			{
				std::string subfile = fileName.substr(num + 1, fileName.size());
				subfiles.push_back(subfile);
				fileName.erase(num, fileName.size());
			}
			else
			{
				fileName.pop_back();
			}
		}
		if (fileName != "")
			subfiles.push_back(fileName);
	}
	static void SeperateQuesMark(std::string fileName, std::list<std::string>& subfiles)
	{
		while (fileName.find_last_of("?") != -1)
		{
			int num = fileName.find_last_of("?") + 1;
			if (num != fileName.size())
			{
				std::string subfile = fileName.substr(num, fileName.size());
				if(subfile != "")
					subfiles.push_back(subfile);
				fileName.erase(num, fileName.size());
			}
			else
			{
				subfiles.push_back("?");
				fileName.pop_back();
			}
		}
		if (fileName != "")
			subfiles.push_back(fileName);
	}
	
	static void GetAllDirAndFiles(std::string path, std::list<std::string>& files)
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
						GetAllDirAndFiles(p.assign(path).append("/").append(fileinfo.name), files);
					}
				}
				else {
					files.push_back(p.assign(path).append("/").append(fileinfo.name));
				}

			} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
			_findclose(hFile);
		}
	}
	static void GetAllFiles(std::string path, std::list<std::string>& files)
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
		std::string respath;
		if (path.find_last_of("/") != -1)
		{
			int num = path.find_last_of("/");
			if (num != path.size())
			{
				respath = path.substr(0,num+1);
			}
		}
		return respath;
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
	static void FindWildcard(std::list<std::string>& files, std::string name)
	{
		std::list<std::string> sepName;
		bool fstStar = false;
		if (*name.begin() == '*')
			fstStar = true;
		SeperateStar(name, sepName);
		for (auto it = files.begin(); it != files.end();)
		{
			if (it->size() < name.size())
			{
				it = files.erase(it);
				continue;
			}
			else
			{
				std::string tmp = *it;
				bool match = true;
				auto sepit = sepName.end();
				do 
				{
					--sepit;
					if (*sepit == "")
					{
						tmp.erase(0);
						break;
					}
					std::list<std::string> sepQues;
					SeperateQuesMark(*sepit, sepQues);		
					auto sepqueIt = sepQues.end();
					do 
					{
						--sepqueIt;
						if (*sepqueIt == "?")
						{
							tmp.erase(0,1);
						}
						else
						{
							int num = tmp.find(*sepqueIt);
							if (-1 == num)
							{
								match = false;
								break;
							}
							else
							{
								if(fstStar)
									tmp.erase(0, num + (*sepqueIt).size());
								else
									tmp.erase(num, num + (*sepqueIt).size());
							}
						}
					} while (sepqueIt != sepQues.begin());
					if (!match)
					{
						break;
					}
					
				} while (sepit != sepName.begin());
				if (tmp != "")
					match = false;
				if (!match)
					it = files.erase(it);
				else
					++it;
			}
		}
		
	}
}
#endif