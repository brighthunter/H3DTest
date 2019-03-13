#include <cstdio>
#include "VirtualDiskManager.h"
#include "PathUtil.h"
#include <Windows.h>
void TestTool()
{
	auto test = PathUtil::GetFileName("E:/虚拟磁盘项目/test/ttt/../test2");
	std::list<std::string> testfiles;
	PathUtil::GetAllFiles("E:/虚拟磁盘项目/test", testfiles);
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
	p->analyzeCommond("lod @e:\\Test");
	p->analyzeCommond("save @e:\\SaveTest\\1");
	p->analyzeCommond("load @e:\\SaveTest\\1");
	p->analyzeCommond("move test1 MoveTest");
	p->analyzeCommond("mklink test aaa");
	p->analyzeCommond("copy test @e:\\Test\\test\\CopyTest");

	p->analyzeCommond("saf @e:\\SaveTest\\Save1");
	/*MEMORYSTATUSEX sysMemStatus;
	sysMemStatus.dwLength = sizeof(sysMemStatus);
	if (!GlobalMemoryStatusEx(&sysMemStatus))
	{
		printf("GlobalMemoryStatusEx fail\n");
		return;
	}
	unsigned long long touse = sysMemStatus.ullTotalVirtual;*/
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
	Test(p);
	std::list<std::string> paths;
	char str[512];
	while(true)
	{
		p->PrintCursor();
		scanf_s("%[^\n]",str,512);
		if (!strcmp(str, "exit"))
			break;
		if (!p->analyzeCommond(str))
			printf("语法命令不正确\n");
		getchar();
		ZeroMemory(str,512);

	}
	delete p;
	
}