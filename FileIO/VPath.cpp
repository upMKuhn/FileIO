#include "FileIO.h"

using namespace FileIO::Common;

namespace FileIO {

	bool VPath::exsist()
	{
		return m_path != "" && !VFS::Get()->Resolve(m_path).exsist();
	}

	VPath VPath::dotdot()
	{
		size_t lastDir = m_path.find_last_of(SLASH);
		return lastDir == 0 ? "\\" : m_path.substr(0, lastDir);
	}

	void VPath::setPath(std::string path)
	{
		path = removeTrailingSlash(path);
		m_path = path;
		m_root = path == "" ||
			(path.find_last_of(SLASH) == 0);
	}

	VPath VPath::Combine(VPath left, VPath right)
	{
		return removeTrailingSlash(left.tostring()).append("\\")
			.append(right.m_path[0] == '\\' ? right.m_path.substr(1) : right);
	}

	Path FileIO::VPath::resolvePath()
	{
		Burp<FileSystem*> fs(FileSystem::get());
		Path path = VFS::Get()->Resolve(*this);
		fs->resolve(path);
		return path;
	}
}