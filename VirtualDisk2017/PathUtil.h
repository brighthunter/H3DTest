#ifndef _PathUtil_H_
#define _PathUtil_H_
#include <string>
#include <vector>
namespace PathUtil
{
	void SeperatePath(std::string Allpath,std::vector<std::string>& subpaths)
	{
		while (Allpath.find_last_of(" ")!= -1)
		{
			int num = Allpath.find_last_of(" ");
			if (num != Allpath.size())
			{
				std::string subpath = Allpath.substr(num, Allpath.size());
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
}
#endif