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
	p->analyzeCommond("copy *t MoveTest");
	p->analyzeCommond("cd MoveTest");
	p->analyzeCommond("dir");
	p->analyzeCommond("mklink From Link");
	p->analyzeCommond("move Link MoveTo");
	return;
	p->analyzeCommond("save @e:\\SaveTest\\1");
	p->analyzeCommond("load @e:\\SaveTest\\1");
	p->analyzeCommond("move test1 MoveTest");
	p->analyzeCommond("mklink test aaa");
	p->analyzeCommond("copy test @e:\\Test\\test\\CopyTest");

	p->analyzeCommond("saf @e:\\SaveTest\\Save1");
	p->analyzeCommond("mklink t.txt test111");
	p->analyzeCommond("md 文档");
	p->analyzeCommond("copy @e:\\文档 文档");
	p->analyzeCommond("lod @e:\\文档");
	p->analyzeCommond("save @e:\\SaveTest\\2");
	p->analyzeCommond("load @e:\\SaveTest\\2");
	

	//getchar();
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
		ZeroMemory(str, 512);
		p->PrintCursor();
		scanf_s("%[^\n]",str,512);
		if (!strcmp(str, "exit"))
			break;
		p->analyzeCommond(str);
		getchar();		

	}
	delete p;
	
}