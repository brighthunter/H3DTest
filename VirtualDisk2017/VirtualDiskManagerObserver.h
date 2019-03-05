#ifndef _VirtualDiskManagerObserver_H_
#define _VirtualDiskManagerObserver_H_
#include "Tool/functor.h"
class VirtualDiskManagerObserver
{
public:
	static VirtualDiskManagerObserver * GetInstance();
	
private:
	VirtualDiskManagerObserver();
	~VirtualDiskManagerObserver();
	static VirtualDiskManagerObserver * m_pInst;
};



#endif