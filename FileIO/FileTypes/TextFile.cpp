#include "FileTypes.h"
using namespace FileIO::Common;


namespace FileIO {

	TextFile::TextFile()
	{
	}

	TextFile::~TextFile()
	{
	}

	bool TextFile::ReadToEnd()
	{
		BurpPointer<FileSystem*> fs(FileSystem::get());
		return fs->readTextFileToEnd(resolvePath(), m_fcontent);
	}

	bool TextFile::Save()
	{
		BurpPointer<FileSystem*> fs = FileSystem::get();
		return fs->writeTextFile(resolvePath(), m_fcontent);
	}

	uint64_t FileIO::TextFile::size()
	{
		return m_fcontent.size();
	}
}
