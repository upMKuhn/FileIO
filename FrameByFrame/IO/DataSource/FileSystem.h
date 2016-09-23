#pragma once
#include <FrameByFrame\Common\Common.h>
#include <FrameByFrame\IO\IO.h>

namespace FrameByFrame::IO
{
	class Path;
	class File;
	
	class FileSystem abstract {
	public:
		virtual bool exsists(Path path) abstract;
		virtual std::string platform() abstract;
		virtual bool isDirectory(Path path) abstract;

		virtual bool mkDir(Path path) abstract;
		virtual bool mkFile(Path path) abstract;
		
		virtual bool deleteFile(Path path) abstract;
		
		virtual bool resolve(Path& path) abstract;
		virtual std::vector<File> lsFiles(Path path) abstract;

		virtual void getFileInfo(File& path) abstract;
		virtual File getFileInfo(Path path) abstract;

		virtual bool fileExsists(Path& p) abstract;
		virtual bool dirExsists(Path& p) abstract;
		
		virtual bool readTextFileToEnd(Path p, std::string& container) abstract;
		virtual bool writeTextFile(Path p, std::string& content) abstract;


		static FileSystem* FileSystem::get();
		
	};

}