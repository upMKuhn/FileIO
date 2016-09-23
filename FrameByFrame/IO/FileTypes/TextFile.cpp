#include "FileTypes.h"
namespace FrameByFrame::IO {

	TextFile::TextFile()
	{
	}

	TextFile::~TextFile()
	{
	}

	bool TextFile::ReadToEnd()
	{
		Burp<FileSystem*> fs(FileSystem::get());
		return fs->readTextFileToEnd(resolvePath(), m_fcontent);
	}

	bool TextFile::Save()
	{
		Burp<FileSystem*> fs = FileSystem::get();
		return fs->writeTextFile(resolvePath(), m_fcontent);
	}

	uint64_t FrameByFrame::IO::TextFile::size()
	{
		return m_fcontent.size();
	}
}
