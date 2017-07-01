#pragma once
#include <vector>
#include <FileIO\FileTypes\File.h>
#include "Path.h"
#include "VPath.h"



namespace FileIO
{
	class FILEIO_API Path;
	class FILEIO_API VPath;

	template class FILEIO_API std::vector<Path>;
	template class FILEIO_API std::map<VPath, std::vector<Path>>;

	class FILEIO_API VFS {

	public:
		VFS();
		~VFS();
		static VFS* Get();

		void Mount(VPath virtualPath, Path physicalPath);
		Path Resolve(VPath virtualPath);

	public:
		static bool exsists(Path path);
		static bool isDirectory(Path path);
		static bool mkDir(Path path);
		static bool mkFile(Path path);
		static bool deleteFile(Path path);
		static bool resolvePath(Path& path);
		static std::vector<File> lsFiles(Path path);
		static void getFileInfo(File& path);
		static File getFileInfo(Path path);
		static bool dirExsists(Path& p);

		static bool readTextFileToEnd(Path p, std::string& container);
		static bool writeTextFile(Path p, std::string& content);
	private:
		std::vector<Path> ResolveDirectory(VPath dir);
		std::map<VPath, std::vector<Path>> m_map;

		bool validVirtualPath(VPath path);
	};

	
}

