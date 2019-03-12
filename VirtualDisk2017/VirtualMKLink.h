#ifndef _VirtualMKLink_H_
#define _VirtualMKLink_H_
#include "VirtualFolder.h"
class VirtualMKLink :public VirtualBlock
{
public:
	VirtualMKLink();
	~VirtualMKLink();
	virtual std::string GetDir(bool linkCursor = false);
	virtual bool CreateVirtualPath(std::list<std::string> subfiles);
	virtual bool DeleteVirtualPath(std::list<std::string> subfiles, int s = 0);
	virtual bool DeleteVirtualPath(std::string fileName = "", int s = 0);
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles, int s = 0);
	virtual bool DeleteVirtualFile(std::string fileName = "",int s = 0);
	virtual bool IsPathEmpty();
	virtual bool IsPath() { return m_isPath; };
	virtual bool IsRoot();
	virtual bool FindPath(std::list<std::string> subfiles);
	virtual bool FindPathFile(std::list<std::string> subfiles);
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName);
	bool Init(std::list<std::string> linkPath, VirtualBlock* root);
	virtual void SetRoot(VirtualBlock* root) { m_root = root; }
	virtual void SetLinkPath(VirtualBlock* root) { m_root = root; }
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files);
	virtual bool GetAllFile(std::list<std::string>& files) ;
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size) ;
	virtual bool GetFileMem(void** mem, int& size);
	virtual int  GetFileSzie();
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles);
	virtual bool SetCursor(std::list<std::string>subfiles);
	virtual bool SetCursor();
	virtual bool ClearCursor();
	virtual void PrintPathMessage(bool hasName);
	virtual void PrintMessage(std::list<std::string> subfiles, int state = 0);
	VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles);
	bool MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root);
	virtual void Save(std::string dst);
	virtual void Clear();
	virtual void EraseChild(std::string);
	virtual void CopyForMove(VirtualBlock*, int state);
	virtual void ClearMap(){ return; }
	virtual void Combine(VirtualBlock*pchild, int state);
	int GetChildrenSize();
	void SetName(const char* oldChildName, const char* newChildName);
private:
	VirtualBlock* m_root;
	std::list<std::string> m_paths;
	bool m_isPath;
	bool m_bCursor = false;
};



#endif