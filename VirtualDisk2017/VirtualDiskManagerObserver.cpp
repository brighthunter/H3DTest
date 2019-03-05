#include "VirtualDiskManagerObserver.h"
VirtualDiskManagerObserver * VirtualDiskManagerObserver::m_pInst = nullptr;
VirtualDiskManagerObserver::VirtualDiskManagerObserver()
{
}

VirtualDiskManagerObserver::~VirtualDiskManagerObserver()
{
}
VirtualDiskManagerObserver * VirtualDiskManagerObserver::GetInstance()
{
	if (!m_pInst)
	{
		m_pInst = new VirtualDiskManagerObserver();
	}
	return m_pInst;
}