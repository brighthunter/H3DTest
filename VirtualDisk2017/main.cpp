#include <cstdio>
#include "VirtualDiskManager.h"
int main()
{
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
		scanf_s("%s",str,512);
		if (!p->analyzeCommond(str))
			printf("Failed\n");


	}
}