#pragma once
#include <FileIO\FileIO.h>

class FileIO::Path;
class FileIO::File;

namespace FileIO {
	
	class FILEIO_API MockFileSystem : public FileSystem
	{
	public:
		static std::map<std::string, bool> m_paths;
		static std::map<std::string, bool> m_isFile;
		static std::map<std::string, std::vector<std::string>> dirFiles;
		static std::map<std::string, std::string> fileContent;

		void reset();
		void MarkAsExsist(Path path, bool mark, bool isFile);

		bool exsists(Path path) override;
		std::string platform() override;
		bool isDirectory(Path path) override;

		bool mkDir(Path path) override;

		bool mkFile(Path path) override;

		bool deleteFile(Path path) override;

		bool resolvePath(Path& path) override;

		std::vector<File> lsFiles(Path path) override;

		bool fileExsists(Path& p) override;
		bool dirExsists(Path& p) override;

		void getFileInfo(File& path);
		File getFileInfo(Path path);

		void MockTextFile(Path p, std::string container);

		bool readTextFileToEnd(Path p, std::string& container) override;

		bool writeTextFile(Path p, std::string& content) override;

	};
}



