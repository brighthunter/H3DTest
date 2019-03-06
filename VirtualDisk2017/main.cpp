#include <cstdio>
#include "VirtualDiskManager.h"
#include "PathUtil.h"
void TestTool()
{
	auto test = PathUtil::GetFileName("E:/ÐéÄâ´ÅÅÌÏîÄ¿/test/ttt/../test2");
	getchar();
}
int main()
{	
	//TestTool();
	VirtualDiskManager *p = new VirtualDiskManager();
	if (!p->Init())
	{
		printf("Create Virtual Disk Failed\n");
		return 0;
	}
	std::vector<std::string> paths;
	char str[512];
	while(true)
	{
		p->PrintCursor();
		scanf_s("%[^\n]",str,512);
		if (!p->analyzeCommond(str))
			printf("Failed\n");
		getchar();

	}
}