#include "MockFileSystem.h"
class FileIO::Path;
class FileIO::File;
namespace FileIO
{

	std::map<std::string, bool> MockFileSystem::m_paths;
	std::map<std::string, bool> MockFileSystem::m_isFile;
	std::map<std::string, std::vector<std::string>> MockFileSystem::dirFiles;
	std::map<std::string, std::string> MockFileSystem::fileContent;

	void FileIO::MockFileSystem::reset()
	{
		m_paths.clear();
		m_isFile.clear();
		dirFiles.clear();
		fileContent.clear();
	}

	void MockFileSystem::MarkAsExsist(Path path, bool mark, bool isFile)
	{
		m_paths[path] = mark;
		m_isFile[path] = isFile;
	}

	bool MockFileSystem::exsists(Path path)  { return m_paths[path]; }
	std::string MockFileSystem::platform()  { return "Mock"; };
	bool MockFileSystem::isDirectory(Path path)  { return exsists(path) && !m_isFile[path]; }

	bool MockFileSystem::mkDir(Path path) 
	{
		m_paths[path] = true;
		m_isFile[path] = false;
		dirFiles[path] = std::vector<std::string>();
		return true;
	}

	bool MockFileSystem::mkFile(Path path) 
	{
		m_paths[path] = true;
		m_isFile[path] = true;
		std::vector<std::string> fd = dirFiles[path];
		fd.push_back(path);
		dirFiles[path] = fd;
		return true;
	}

	bool MockFileSystem::deleteFile(Path path) 
	{
		bool val = m_paths[path];
		m_paths[path] = false;
		return val;
	}

	bool MockFileSystem::resolvePath(Path& path) 
	{
		return true;
	}

	std::vector<File> MockFileSystem::lsFiles(Path path) 
	{
		std::vector<File> result;

		for (std::string& str : dirFiles[path])
		{
			if (exsists(str))
				result.push_back(File(str));
		}
		return result;
	}

	bool MockFileSystem::fileExsists(Path& p)  { return m_paths[p] && m_isFile[p]; }
	bool MockFileSystem::dirExsists(Path& p)  { return m_paths[p] && !m_isFile[p]; }

	void MockFileSystem::getFileInfo(File& path) { path.size(0); };
	File MockFileSystem::getFileInfo(Path path) { File f(path.tostring(), 0); return f; };

	void MockFileSystem::MockTextFile(Path p, std::string container)
	{
		mkFile(p);
		fileContent[p] = container;
	}

	bool MockFileSystem::readTextFileToEnd(Path p, std::string& container) 
	{
		container.empty();
		container.resize(fileContent[p].size());
		container = fileContent[p];
		return true;
	}

	bool MockFileSystem::writeTextFile(Path p, std::string& content) 
	{
		mkFile(p);
		MockTextFile(p, content);
		return true;
	}


}