#include "MockFileSystem.h"
class FileIO::IO::Path;
class FileIO::IO::File;
namespace FileIO::IO
{

	std::map<std::string, bool> MockFileSystem::paths;
	std::map<std::string, bool> MockFileSystem::m_File;
	std::map<std::string, std::vector<std::string>> MockFileSystem::dirFiles;
	std::map<std::string, std::string> MockFileSystem::fileContent;

#ifdef UNIT_TESTS
	FileSystem* FileSystem::get()
	{
		return new MockFileSystem();
	}
#endif

	inline void MockFileSystem::MarkAsExsist(Path path, bool mark, bool isFile)
	{
		paths[path] = mark;
		m_File[path] = isFile;
	}

	inline bool MockFileSystem::exsists(Path path)  { return paths[path]; }
	inline std::string MockFileSystem::platform()  { return "Mock"; };
	inline bool MockFileSystem::isDirectory(Path path)  { return exsists(path) && !m_File[path]; }

	inline bool MockFileSystem::mkDir(Path path) 
	{
		paths[path] = true;
		m_File[path] = false;
		dirFiles[path] = std::vector<std::string>();
		return true;
	}

	inline bool MockFileSystem::mkFile(Path path) 
	{
		paths[path] = true;
		m_File[path] = true;
		std::vector<std::string> fd = dirFiles[path];
		fd.push_back(path);
		dirFiles[path] = fd;
		return true;
	}

	inline bool MockFileSystem::deleteFile(Path path) 
	{
		bool val = paths[path];
		paths[path] = false;
		return val;
	}

	inline bool MockFileSystem::resolve(Path& path) 
	{
		return true;
	}

	inline std::vector<File> MockFileSystem::lsFiles(Path path) 
	{
		std::vector<File> result;

		for (std::string& str : dirFiles[path])
		{
			if (exsists(str))
				result.push_back(File(str));
		}
		return result;
	}

	inline bool MockFileSystem::fileExsists(Path& p)  { return paths[p] && m_File[p]; }
	inline bool MockFileSystem::dirExsists(Path& p)  { return paths[p] && !m_File[p]; }

	inline void MockFileSystem::getFileInfo(File& path) { path.size(0); };
	inline File MockFileSystem::getFileInfo(Path path) { File f(path.tostring(), 0); return f; };

	inline void MockFileSystem::MockTextFile(Path p, std::string container)
	{
		mkFile(p);
		fileContent[p] = container;
	}

	inline bool MockFileSystem::readTextFileToEnd(Path p, std::string& container) 
	{
		container.empty();
		container.resize(fileContent[p].size());
		container = fileContent[p];
		return true;
	}

	inline bool MockFileSystem::writeTextFile(Path p, std::string& content) 
	{
		mkFile(p);
		MockTextFile(p, content);
		return true;
	}


}