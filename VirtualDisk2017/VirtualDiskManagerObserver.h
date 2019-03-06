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
	void Register_AddCursor(Functor1<VirtualFolder*> func) { m_func1 = func; }
	void Register_DeletePath(Functor2wRet<const char*, bool,bool> func) { m_func2 = func; }
	//Notify
	bool Notify_CreatePath(const char* userInput) { return m_func(userInput); }
	void Notify_AddCursor(VirtualFolder* vf) { m_func1(vf); }
	void Notify_DeletePath(const char* userInput,bool s = false) { m_func2(userInput,s); }
private:
	VirtualDiskManagerObserver();
	~VirtualDiskManagerObserver();
	static VirtualDiskManagerObserver * m_pInst;
	Functor1wRet<const char*, bool> m_func;
	Functor1<VirtualFolder*> m_func1;
	Functor2wRet<const char*,bool, bool> m_func2;
};



#endif