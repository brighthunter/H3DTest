#ifndef _StringUtil_H_
#define _StringUtil_H_
#include <string>
namespace StringUtil 
{
	static void AddDot(std::string& input)
	{
		size_t len = input.length();
		for (int index = (int)len - 3; index > 0; index -= 3)
			input.insert(index, ",");
	}
	

}
#endif // !StringUtil_H_
