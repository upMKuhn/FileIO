#pragma once
#include <FrameByFrame\IO\IO.h>
//INCLUDE LIB !!! Shlwapi.lib
class FrameByFrame::IO::Path;
class FrameByFrame::IO::File;



namespace FrameByFrame::IO {
	class WindowsFilesys : public FileSystem {
	public:

		bool exsists(Path path) override;
		bool isDirectory(Path path) override;
		bool mkDir(Path path) override;
		bool mkFile(Path path) override;
		bool deleteFile(Path path) override;
		bool WindowsFilesys::readfile(File& f);
		bool readTextFileToEnd(Path p, std::string& container) override;
		bool writeTextFile(Path p, std::string& content) override;


		bool resolve(Path& path) override;
		bool fileExsists(Path& p) override;
		bool dirExsists(Path& p) override;
		
		std::vector<File> lsFiles(Path path) override;

		void getFileInfo(File& file) override;
		File getFileInfo(Path path) override;

		std::string platform() override;
	};
}

