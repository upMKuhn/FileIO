#pragma once
#include <FrameByFrame\IO\IO.h>

class FrameByFrame::IO::Path;
class FrameByFrame::IO::File;

namespace FrameByFrame::IO {
	
	class MockFileSystem : public FileSystem
	{
	public:
		static std::map<std::string, bool> paths;
		static std::map<std::string, bool> m_File;
		static std::map<std::string, std::vector<std::string>> dirFiles;
		static std::map<std::string, std::string> fileContent;


		inline void MarkAsExsist(Path path, bool mark, bool isFile);

		inline bool exsists(Path path) override;
		inline std::string platform() override;
		inline bool isDirectory(Path path) override;

		inline bool mkDir(Path path) override;

		inline bool mkFile(Path path) override;

		inline bool deleteFile(Path path) override;

		inline bool resolve(Path& path) override;

		inline std::vector<File> lsFiles(Path path) override;

		inline bool fileExsists(Path& p) override;
		inline bool dirExsists(Path& p) override;

		inline void getFileInfo(File& path);
		inline File getFileInfo(Path path);

		inline void MockTextFile(Path p, std::string container);

		inline bool readTextFileToEnd(Path p, std::string& container) override;

		inline bool writeTextFile(Path p, std::string& content) override;

	};
}



