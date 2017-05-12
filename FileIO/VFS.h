#pragma once
#include "FileIO.h"
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
	private:
		std::vector<Path> ResolveDirectory(VPath dir);
		std::map<VPath, std::vector<Path>> m_map;

		bool validVirtualPath(VPath path);
	};

	
}

