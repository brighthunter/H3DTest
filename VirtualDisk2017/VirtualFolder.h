#ifndef _VirtualFolder_H_
#define _VirtualFolder_H_
#include "VirtualBlock.h"

class VirtualFolder :public VirtualBlock
{
public:
	VirtualFolder(void);
	~VirtualFolder(void);
	virtual std::string GetDir(bool linkCursor = false);
	virtual bool CreateVirtualPath(std::list<std::string> subfiles);
	virtual bool DeleteVirtualPath(std::list<std::string> subfiles,int s = 0);
	virtual bool DeleteVirtualPath(std::string subfiles, int s);
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles,int s = 0);
	virtual bool DeleteVirtualFile(std::string fileName = "",int s = 0);
	virtual bool IsPathEmpty();
	virtual bool IsPath();
	virtual bool IsRoot();
	virtual bool FindPath(std::list<std::string> subfiles);
	virtual bool FindFile(std::list<std::string> subfiles);
	virtual bool FindPathFile(std::list<std::string> subfiles);
	virtual bool CreateVirtualFile(void *mem,int fsize, std::list<std::string> virtualFiles,const char* dstName);
	virtual bool CreateVirtualFile(void *mem,int fsize,const char* dstName);
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files);
	virtual bool GetAllFile(std::list<std::string>& files);
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size);
	virtual bool GetFileMem(void** mem, int& size) { return false; }
	virtual int  GetFileSzie() { return 0; }
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles);
	virtual void SetName(const char* name) { __super::SetName(name); }
	virtual void SetName(const char* oldChildName, const char* newChildName);
	virtual bool SetCursor(std::list<std::string> subfiles);
	virtual bool SetCursor();
	virtual bool ClearCursor();
	virtual bool PrintDir(std::list<std::string>subfiles, int state);
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles);
	virtual void SetRoot(bool broot) { m_broot = broot; m_bCursor = true; }
	virtual void PrintPathMessage(bool hasName);
	virtual void PrintMessage(std::list<std::string> subfiles, int state);
	virtual bool MkLink(std::list<std::string> src, std::list<std::string> dst,VirtualBlock* root);
	virtual void Save(std::string dst);
	virtual void Load(std::string src);
	virtual int GetChildrenSize();
	void Clear();
	void ClearMap();
	void Combine(VirtualBlock*pchild, int state);
	void GetChildren(std::list<VirtualBlock*>&pchildren);
	void Move(std::list<std::string> src, std::list<std::string> dst,int state);
	void EraseChild(std::string);
	void CopyForMove(VirtualBlock*,int state);
	void Serialize(const char* dst);
	void DeSerialize(const char* src);
	void Encode(std::ofstream& of);
	void Decode(std::ifstream& inf);
private:
	std::map<std::string, VirtualBlock*> m_vfChildren;
	bool m_bCursor = false;
	bool m_broot = false;
	static int g_cacheType;
	static std::string g_cacheName;
	
	
};
#endif