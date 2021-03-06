#ifndef _VirtualFile_H_
#define _VirtualFile_H_
#include "VirtualBlock.h"
class VirtualFile :public VirtualBlock
{
public:
	VirtualFile();
	~VirtualFile();
	virtual std::string GetDir(bool linkCursor = false) { return ""; }
	virtual bool CreateVirtualPath(std::list<std::string> subfiles) { return false; }
	virtual bool DeleteVirtualPath(std::list<std::string> subfiles, int s = 0) { return false; }
	virtual bool DeleteVirtualPath(std::string fileName = "", int s = 0) { return false; }
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles, int s = 0) { return false; }
	virtual bool DeleteVirtualFile(std::string fileName = "",int s = 0) { return false; }
	virtual bool SetMemory(void* mem, int memSize);
	virtual bool IsPathEmpty() { return false; }
	virtual bool IsPath() { return false; }
	virtual bool IsRoot() { return false; }
	virtual bool FindPath(std::list<std::string> subfiles) { return false; }
	virtual bool FindPathFile(std::list<std::string> subfiles) { return false; }
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) { return false; };
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files) { return false; }
	virtual bool GetAllFile(std::list<std::string>& files) { files.push_back(m_name); return true; }
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size) { return false; }
	virtual bool GetFileMem(void** mem, int& size);
	virtual int  GetFileSzie() { return m_size; }
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles) { return false; }
	virtual bool SetCursor(std::list<std::string>subfiles) { return false; }
	virtual bool SetCursor() { return false; }
	virtual bool ClearCursor() { return true; }
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles);
	virtual void PrintMessage(std::list<std::string> subfiles, int state);
	virtual void PrintPathMessage(bool hasName) { return; }
	virtual bool MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root) { return false; }
	virtual void Save(std::string dst);
	virtual void Load(std::string src);
	virtual void Clear() {}
	virtual void ClearMap() {};
	virtual void EraseChild(std::string cname);
	virtual void CopyForMove(VirtualBlock*, int state) { return; }
	virtual void Combine(VirtualBlock*pchild, int state);
	virtual int GetChildrenSize() { return 0; }
	virtual void SetName(const char* oldChildName, const char* newChildName) { return; }
	virtual void Encode(std::ofstream& of);
	virtual bool Decode(std::ifstream& inf);
	virtual void GetChildren(std::list<VirtualBlock*>&pchildren) {}
private:
	void* m_mem = nullptr;
	int m_size = 0;
};


#endif