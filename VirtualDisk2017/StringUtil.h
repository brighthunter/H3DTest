#ifndef _StringUtil_H_
#define _StringUtil_H_
#include <string>
#include <vector>
#include <fstream>
namespace StringUtil 
{
	static void AddDot(std::string& input)
	{
		size_t len = input.length();
		for (int index = (int)len - 3; index > 0; index -= 3)
			input.insert(index, ",");
	}
	static void VecToString(std::string &str, std::vector<char> Vec)
	{
		str.clear();
		for (size_t it = 0; it < Vec.size(); it++)
		{
			str.push_back(Vec[it]);
			
		}
	}
	static void ReadString(std::ifstream &inf,std::string &str,int size)
	{
		char* strtmp = new char[size + 1];
		strtmp[size] = 0;
		inf.read(strtmp, size);
		str = strtmp;
		delete[] strtmp;
	}
}
#endif // !StringUtil_H_
