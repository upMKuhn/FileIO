#pragma once
#include <FileIO\Common\Common.h>
#include <FileIO\FileIO.h>

namespace FileIO
{
	class Path;
	class File;
	
	class FILEIO_API FileSystem abstract {
	public:
		virtual bool exsists(Path path) abstract;
		virtual std::string platform() abstract;
		virtual bool isDirectory(Path path) abstract;

		virtual bool mkDir(Path path) abstract;
		virtual bool mkFile(Path path) abstract;
		
		virtual bool deleteFile(Path path) abstract;
		
		virtual bool resolvePath(Path& path) abstract;
		virtual std::vector<File> lsFiles(Path path) abstract;

		virtual void getFileInfo(File& path) abstract;
		virtual File getFileInfo(Path path) abstract;

		virtual bool fileExsists(Path& p) abstract;
		virtual bool dirExsists(Path& p) abstract;
		
		virtual bool readTextFileToEnd(Path p, std::string& container) abstract;
		virtual bool writeTextFile(Path p, std::string& content) abstract;

		//Use Stubbed File system or not?
		enum FileSystemMode { FS_MODE_MEMORY = 1, FS_MODE_PHYSICAL = 2};
		static void FileSystem::setMode(FileSystemMode mode);
		static FileSystem* FileSystem::get();
	};

}