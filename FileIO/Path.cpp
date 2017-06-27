#include "FileIO.h"

using namespace FileIO::Common;

namespace FileIO {

	void Path::setPath(std::wstring p)
	{
		std::string path(p.begin(), p.end());
		m_path = Common::removeTrailingSlash(path);
		m_wpath = Common::removeTrailingSlash(p);
	}

	void Path::setPath(std::string p)
	{
		std::wstring path(p.begin(), p.end());
		m_path = Common::removeTrailingSlash(p);
		m_wpath = Common::removeTrailingSlash(path);
	}

	bool Path::exsist()
	{
		if (m_path == "") return false;
		BurpPointer<FileSystem*> fs = FileSystem::get();
		return fs->exsists(*this);
	}

	bool Path::isFile()
	{
		size_t lastDot = m_path.find_last_of('.');
		size_t lastSlash = m_path.find_last_of(FILEIO_SLASH);
		return lastSlash < lastDot && lastDot != m_path.npos;
	}

	std::string Path::filename()
	{
		if (!isFile()) return "";
		return m_path.substr(m_path.find_last_of(FILEIO_SLASH)+1);
	}

	std::string Path::filenameWihtoutExtension()
	{
		if (!isFile()) return "";
		std::string fname = filename();
		return fname.substr(0, fname.find_last_of('.'));
	}

	std::string Path::fileExtension()
	{
		if (!isFile()) return "";
		std::string fname = filename();
		return fname.substr(fname.find_last_of('.'));
	}

	Path Path::directory()
	{
		std::string newPath = m_path;
		if (isFile() && m_path.size() > 0)
		{
			size_t slash = m_path.find_last_of(FILEIO_SLASH);
			newPath = newPath.substr(0, max(slash, 1));
		}
		return newPath;
	}

	Path Path::Combine(Path left, Path right)
	{
		if (right.empty()) return left;
		StringBuilder<char> builder(left);
		builder.Append("\\");
		builder.Append(right.m_path[0] == '\\' ? right.m_path.substr(1) : right);
		return Path(builder.ToString());
	}
	
	bool Path::equals(Path& other) {
		using namespace std;
		if (other.empty() || this->empty())
		return other.empty() && this->empty();

		wstring strOther = stringToLower(other.towstring());
		wstring strMe = stringToLower(other.towstring());
		return strMe.compare(strOther) != 0;
	}

}