#include "VirtualFile.h"
#include "StringUtil.h"
VirtualFile::VirtualFile()
{
	m_type = FILE_BLOCK;
}

VirtualFile::~VirtualFile()
{
	if (m_size > 0)
	{
		m_size = 0;
		free(m_mem);
	}
}
bool VirtualFile::SetMemory(void* mem, int memSize)
{
	if (memSize != 0)
	{
		m_size = memSize;
		m_mem = malloc(memSize);
		memcpy(m_mem, mem, memSize);
	}
	return true;
}
bool VirtualFile::GetFileMem(void** mem, int& size)
{
	if (m_size == 0)
		return false;
	*mem = m_mem;
	size = m_size;
	return true;
}
VirtualBlock* VirtualFile::GetVirtualPoint(std::list<std::string>subfiles)
{
	if (m_name == subfiles.back())
	{
		subfiles.pop_back();
		if(subfiles.size() == 0)
			return this;
	}
	return nullptr;
}
void VirtualFile::PrintMessage(std::list<std::string> subfiles, int state)
{
	auto strMemsize = std::to_string(m_size);
	StringUtil::AddDot(strMemsize);
	printf("%s  %s%18s %s\n", m_datetime, m_daytime, strMemsize.c_str(), m_name.c_str());
}
void VirtualFile::Save(std::string dst)
{
	std::string dstName = dst + "/" + m_name;
	FILE* _file;
	fopen_s(&_file, dstName.c_str(), "wb");
	fwrite(m_mem, m_size, 1, _file);
	fclose(_file);
}
void VirtualFile::Load(std::string src)
{

}
void VirtualFile::EraseChild(std::string cname)
{
	return;
}

void VirtualFile::Combine(VirtualBlock*pchild, int state)
{
	return;
}
void VirtualFile::Encode(std::ofstream& of)
{
	__super::Encode(of);
	of << m_size << STREND;
	of.write((char*)m_mem, m_size);
	of << STREND;
}
void VirtualFile::Decode(std::ifstream& inf)
{
	inf >> m_datetime >> m_daytime >> m_size;
	m_mem = malloc(m_size);
	char strEnd;
	inf.read((char*)&strEnd, 1);
	inf.read((char*)m_mem, m_size);
}