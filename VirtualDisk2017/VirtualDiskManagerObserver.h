#ifndef _VirtualDiskManagerObserver_H_
#define _VirtualDiskManagerObserver_H_
#include "Tool/functor.h"
class VirtualFolder;
class VirtualDiskManagerObserver
{
public:
	static VirtualDiskManagerObserver * GetInstance();
	//Register
	void Register_CreatePath(Functor1wRet<const char*, bool> func) { m_func = func; }
	void Register_AddCursor(Functor1<const char*> func) { m_func1 = func; }
	void Register_DeletePath(Functor2wRet<const char*, bool, bool> func) { m_func2 = func; }
	void Register_CopyPath(Functor2wRet<std::string, std::string, bool> func) { m_func3 = func; }
	void Register_Rename(Functor2<const char*, const char*> func) { m_func4 = func; }
	void Register_SetCursor(Functor1<const char*> func) { m_func5 = func; }
	void Register_DeleteVirtualFile(Functor2<const char*, int>func) { m_func6 = func; }
	void Register_PrintDir(Functor2<const char*,int> func) { m_func7 = func; }
	void Register_Mklink(Functor2<const char*, const char*> func) { m_func8 = func; }
	void Register_Save(Functor1<const char*> func) { m_func9 = func; }
	void Register_Load(Functor1<const char*> func) { m_func10 = func; }
	void Register_Move(Functor3<const char*,const char*,int> func) { m_func11 = func; }
	//Notify
	bool Notify_CreatePath(const char* userInput) { return m_func(userInput); }
	void Notify_AddCursor(const char* vf) { m_func1(vf); }
	void Notify_DeletePath(const char* userInput,bool s = false) { m_func2(userInput,s); }
	bool Notify_CopyPath(std::string src, std::string dst) { return m_func3(src, dst);  }
	void Notify_Rename(const char* src, const char* dst) { m_func4(src,dst); }
	void Notify_SetCursor(const char* dst) { m_func5(dst); }
	void Notify_DeleteVirtualFile(const char* name,int s) { m_func6(name,s); }
	void Notify_PrintDir(const char* userInput, int state) { m_func7(userInput, state); }
	void Notify_Mklink(const char* src, const char* dst) { m_func8(src, dst); }
	void Notify_Save(const char* dst) { m_func9(dst); }
	void Notify_Load(const char* dst) { m_func10(dst); }
	void Notify_Move(const char* src, const char* dst, int state) { m_func11(src,dst,state); }
private:
	VirtualDiskManagerObserver();
	~VirtualDiskManagerObserver();
	static VirtualDiskManagerObserver * m_pInst;
	Functor1wRet<const char*, bool> m_func;
	Functor1<const char*> m_func1;
	Functor2wRet<const char*,bool, bool> m_func2;
	Functor2wRet<std::string, std::string, bool> m_func3;
	Functor2<const char*, const char*> m_func4;
	Functor1<const char*> m_func5;
	Functor2<const char*,int> m_func6;
	Functor2<const char*, int> m_func7;
	Functor2<const char*, const char*> m_func8; 
	Functor1<const char*> m_func9;
	Functor1<const char*> m_func10;
	Functor3<const char*, const char*, int> m_func11;
};



#endif