#include <FileIO\FileIO.h>

namespace FileIO {
	FileSystem::FileSystemMode fileSystemMode;
	void FileSystem::setMode(FileSystemMode mode)
	{
		fileSystemMode = mode;
	}

	FileSystem* FileSystem::get()
	{
		if (fileSystemMode == FS_MODE_MEMORY)
			return new MockFileSystem();
		else {
			#ifdef FILEIO_WINDOWS
				return new WindowsFilesys();
			#endif
		}
	}
}