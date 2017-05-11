#pragma once
#include <FileIO\FileIO.h>
//INCLUDE LIB !!! Shlwapi.lib
class FileIO::Path;
class FileIO::File;

#ifdef FILEIO_WINDOWS
#include <FileIO\Common\Dependencies\Windows\dirent.h>

namespace FileIO {
	class FILEIO_API WindowsFilesys : public FileSystem {
	public:

		bool exsists(Path path) override;
		bool isDirectory(Path path) override;
		bool mkDir(Path path) override;
		bool mkFile(Path path) override;
		bool deleteFile(Path path) override;
		bool readfile(File& f);
		bool readTextFileToEnd(Path p, std::string& container) override;
		bool writeTextFile(Path p, std::string& content) override;


		bool resolvePath(Path& path) override;
		bool fileExsists(Path& p) override;
		bool dirExsists(Path& p) override;
		
		std::vector<File> lsFiles(Path path) override;

		void getFileInfo(File& file) override;
		File getFileInfo(Path path) override;

		std::string platform() override;
	};
}
#endif

