#include "FileIO.h"
#include "private\__IO_Dependencies.h"
using namespace FileIO::Common;

namespace FileIO
{

	VFS* _vfs_instance = nullptr;

	VFS* VFS::Get()
	{ 
		if (_vfs_instance == nullptr)
			_vfs_instance = new VFS();
		return _vfs_instance;
	}

	double average(int count, ...)
	{
		va_list ap;
		int j;
		double tot = 0;
		va_start(ap, count); //Requires the last fixed parameter (to get the address)
		for (j = 0; j < count; j++)
			tot += va_arg(ap, double); //Requires the type to cast to. Increments ap to the next argument.
		va_end(ap);
		return tot / count;
	}

	VFS::VFS()
	{
	}

	VFS::~VFS()
	{
	}

	void VFS::Mount(VPath virtualPath, Path physicalPath)
	{
		using namespace std;
		virtualPath = removeTrailingSlash(virtualPath.tostring());
		physicalPath = physicalPath.directory();
		vector<Path> list = m_map[virtualPath];
		bool shouldPush = list.empty();

		//avoid duplicats
		if (find(list.begin(), list.end(), physicalPath) == list.end())
			list.push_back(physicalPath);
		m_map[virtualPath] = list;
	}

	//To Do --> choos right directory of vector..
	Path VFS::Resolve(VPath virtualPath)
	{
		Path rPath = "";
		std::vector<Path> list = ResolveDirectory(virtualPath);
		BurpPointer<FileSystem*> filesystem = FileSystem::get();

		for (Path& path : list)
			if (filesystem->exsists(path))
			{
				rPath = path;
				break;
			}

		if (rPath == Path("") && list.size() > 0) {
			rPath = list[0];
			filesystem->resolvePath(rPath);
		}
		else if (rPath == Path("")) {
			rPath = virtualPath;
		}

		return rPath;
	}
	
	std::vector<Path> VFS::ResolveDirectory(VPath dir)
	{
		VPath newDir(dir.directory().tostring());
		while (!validVirtualPath(dir) && !newDir.IsRoot())
			newDir = newDir.dotdot();
		std::vector<Path> paths = m_map[newDir];
		for (Path& p : paths)
			p.Combine(dir.tostring().substr(newDir.tostring().size()));
		return paths;
	}

	bool VFS::validVirtualPath(VPath path)
	{ return  m_map.count(path) > 0 && !m_map[path].empty(); }


	bool VFS::exsists(Path path)
	{
		return VFS::Get()->exsists(path);
	}

	bool VFS::isDirectory(Path path)
	{
		return VFS::Get()->isDirectory(path);
	}

	bool VFS::mkDir(Path path)
	{
		return VFS::Get()->mkDir(path);
	}

	bool VFS::mkFile(Path path)
	{
		return VFS::Get()->mkDir(path);
	}

	bool VFS::deleteFile(Path path)
	{
		return VFS::Get()->deleteFile(path);
	}

	bool VFS::resolvePath(Path& path)
	{
		return VFS::Get()->resolvePath(path);
	}

	std::vector<File> VFS::lsFiles(Path path)
	{
		return VFS::Get()->lsFiles(path);
	}

	void VFS::getFileInfo(File & path)
	{
		VFS::Get()->getFileInfo(path);
	}

	File VFS::getFileInfo(Path path)
	{
		return VFS::Get()->getFileInfo(path);
	}

	bool VFS::dirExsists(Path & p)
	{
		return VFS::Get()->dirExsists(p);
	}

	bool VFS::readTextFileToEnd(Path p, std::string & container)
	{
		return VFS::Get()->readTextFileToEnd(p, container);
	}

	bool VFS::writeTextFile(Path p, std::string & content)
	{
		return VFS::Get()->writeTextFile(p, content);
	}
}