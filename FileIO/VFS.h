#pragma once
#include "FileIO.h"
#include "VPath.h"
#include <FileIO\FileTypes\File.h> 
#include <FileIO\FileTypes\TextFile.h> 


namespace FileIO
{
	class File;
	class FILEIO_API Path;
	class FILEIO_API VPath;

	template class FILEIO_API std::vector<Path>;
	template class FILEIO_API std::map<VPath, std::vector<Path>>;

	class FILEIO_API VFS {
	private: 
		std::map<VPath, std::vector<Path>> m_map;

	public:
		VFS();
		~VFS();
		static VFS* Get();

		static bool exsists(VPath path);
		static bool isDirectory(VPath path);

		static bool mkDir(VPath path);
		static bool mkFile(VPath path);

		static bool deleteFile(VPath path);

		static std::vector<File> lsFiles(VPath path);

		static File getFileInfo(VPath path);

		static bool fileExsists(VPath& p);
		static bool dirExsists(VPath& p);

		static bool readTextFileToEnd(VPath p, std::string& container);
		static bool writeTextFile(VPath p, std::string& content);


		void Mount(VPath virtualPath, Path physicalPath);
		Path Resolve(VPath virtualPath);
	private:
		bool validVirtualPath(VPath path);
		std::vector<Path> ResolveDirectory(VPath dir);


	};

	
}

