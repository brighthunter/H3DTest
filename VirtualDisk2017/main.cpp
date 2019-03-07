#include <cstdio>
#include "VirtualDiskManager.h"
#include "PathUtil.h"
void TestTool()
{
	auto test = PathUtil::GetFileName("E:/ĞéÄâ´ÅÅÌÏîÄ¿/test/ttt/../test2");
	std::list<std::string> testfiles;
	PathUtil::GetAllFiles("E:/ĞéÄâ´ÅÅÌÏîÄ¿/test", testfiles);
	for (auto it = testfiles.begin(); it != testfiles.end(); it++)
	{
		*it = PathUtil::GetFileName(*it);
	}
	PathUtil::FindWildcard(testfiles, "12*d??6.txt");
	getchar();
}
void Test(VirtualDiskManager *p)
{
	p->analyzeCommond("md Test");
	p->analyzeCommond("md Test1");
	p->analyzeCommond("copy @e:\\Test\\t.txt Test");
	p->analyzeCommond("copy Test\\t.txt Test1");
	p->analyzeCommond("copy Test1\\t.txt @e:\\Test\\1\\");
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
	Test(p);
	std::list<std::string> paths;
	char str[512];
	while(true)
	{
		p->PrintCursor();
		scanf_s("%[^\n]",str,512);
		if (!p->analyzeCommond(str))
			printf("Failed\n");
		getchar();

	}
	delete p;
	
}