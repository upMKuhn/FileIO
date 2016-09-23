#include "IO.h"
#include "private\__IO_Dependencies.h"

namespace FrameByFrame::IO
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
		Burp<FileSystem*> fs = FileSystem::get();

		for (Path& path : list)
			if (fs->exsists(path))
			{
				rPath = path;
				break;
			}

		//Path not pointing to known file or folder
		if (rPath == Path("")) rPath = list[0];

		fs->resolve(rPath);
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
}