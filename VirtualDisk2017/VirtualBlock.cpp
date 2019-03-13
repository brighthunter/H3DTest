#include "VirtualBlock.h"
#include <time.h>
VirtualBlock::VirtualBlock()
{
}

VirtualBlock::~VirtualBlock()
{
	m_pParent = nullptr;
}
bool VirtualBlock::SetTimeNow()
{
	time_t nowtime;
	nowtime = time(NULL);
	struct tm local;
	localtime_s(&local, &nowtime);
	sprintf_s(m_datetime, "%d/%02d/%02d", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
	sprintf_s(m_daytime, "%02d:%02d", local.tm_hour, local.tm_min);
	return true;
}
bool VirtualBlock::Init(VirtualBlock* pParent)
{
	m_pParent = pParent;
	return SetTimeNow();
}
void VirtualBlock::Encode(std::ofstream& of)
{
	int type = m_type;
	of << type << STREND << GetParent()->GetName().length() << STREND << GetParent()->GetName() << STREND << m_name.length() << STREND << m_name << STREND << m_datetime << STREND << m_daytime << STREND;
}