#include "FileTypes.h"
using namespace FileIO::Common;

namespace FileIO
{
	File::operator const wchar_t*() { return m_wpath.c_str(); }
	File::operator const char*() { return m_path.c_str();}
	File::operator std::string() { return m_path.c_str();}
	File::operator std::wstring() { return m_wpath;}

	File::~File()
	{
	}

	uint64_t File::size()
	{
		Burp<FileSystem*> fs(FileSystem::get());
		if (f_length == UINT64_MAX)
			fs->getFileInfo(*this);
		return f_length;
	}

}
