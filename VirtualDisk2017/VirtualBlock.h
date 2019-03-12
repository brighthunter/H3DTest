#ifndef _VirtualBlock_H_
#define _VirtualBlock_H_
#include <string>
#include <map>
#include <list>
enum BlockType
{
	FLOLDER_BLOCK,
	FILE_BLOCK,
	MKLINK_BLOCK
};
class VirtualBlock
{
public:
	VirtualBlock();
	virtual ~VirtualBlock() = 0;
	virtual std::string GetDir(bool linkCursor = false) = 0;
	virtual bool CreateVirtualPath(std::list<std::string> subfiles) = 0;
	virtual bool DeleteVirtualPath(std::list<std::string> subfiles, int s = 0) = 0;
	virtual bool DeleteVirtualPath(std::string fileName = "", int s = 0) = 0;
	virtual bool DeleteVirtualFile(std::list<std::string> subfiles, int s = 0) = 0;
	virtual bool DeleteVirtualFile(std::string fileName ="",int s = 0) = 0;
	virtual bool IsPathEmpty() = 0;
	virtual bool IsPath() = 0;
	virtual bool IsRoot() = 0;
	virtual bool FindPath(std::list<std::string> subfiles) = 0;
	virtual bool FindPathFile(std::list<std::string> subfiles) = 0;
	virtual bool CreateVirtualFile(void *mem, int fsize, const char* dstName) = 0;
	virtual bool Init(VirtualBlock* pfather);
	virtual bool GetAllFile(std::list<std::string>paths, std::list<std::string>& files) = 0;
	virtual bool GetAllFile(std::list<std::string>& files) = 0;
	virtual bool GetFileMem(std::list<std::string> srcPaths, void** mem, int& size) = 0;
	virtual bool GetFileMem(void** mem, int& size) = 0;
	virtual int  GetFileSzie() = 0;
	virtual void SetName(const char* name) { m_name = name; }
	virtual void SetName(const char* oldChildName, const char* newChildName) = 0;
	virtual std::string GetName() { return m_name; }
	virtual bool RenamePathFile(const char* name, std::list<std::string>subfiles) = 0;
	virtual bool SetCursor(std::list<std::string>subfiles) = 0;
	virtual bool SetCursor() = 0;
	virtual bool ClearCursor() = 0;
	virtual VirtualBlock* GetVirtualPoint(std::list<std::string>subfiles) = 0;
	virtual void PrintPathMessage(bool hasName) = 0;
	virtual void PrintMessage(std::list<std::string> subfiles,int state = 0) = 0;
	virtual bool MkLink(std::list<std::string> src, std::list<std::string> dst, VirtualBlock* root) = 0;
	virtual void Save(std::string dst) = 0;
	virtual void Clear() = 0;
	virtual void ClearMap() = 0;
	virtual void EraseChild(std::string name) = 0;
	virtual void CopyForMove(VirtualBlock*, int state) = 0;
	virtual void Combine(VirtualBlock*pchild, int state) = 0;
	virtual int GetChildrenSize() = 0;
	virtual VirtualBlock* GetParent() { return m_pParent; }
	virtual void Encode(std::ofstream& of) = 0;
	virtual void Decode(std::ifstream& inf) = 0;
protected:
	char m_datetime[32];
	char m_daytime[32];
	std::string m_name;
	bool m_bpredel;
	VirtualBlock* m_pParent = nullptr;
	BlockType m_type;
private:
	virtual bool SetTimeNow();
};


#endif