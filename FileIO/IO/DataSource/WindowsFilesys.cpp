
#include <IO\IO.h>
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>

using namespace FileIO::Common;
namespace FileIO::IO {
	
#ifdef WINDOWS
#ifndef UNIT_TESTS
	FileSystem* FileSystem::get()
	{
		return new WindowsFilesys();
	}
#endif
#endif

	bool WindowsFilesys::exsists(Path path)
	{
		if (path.isFile()) return fileExsists(path);
		else return dirExsists(path);
	}

	bool WindowsFilesys::dirExsists(Path& p)
	{
		resolve(p);
		DWORD ftyp = GetFileAttributesA(p);
		DWORD error = GetLastError();
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!

		return false;    // this is not a directory!
	}

	bool WindowsFilesys::fileExsists(Path & p)
	{
		resolve(p);
		return PathFileExists(p) == TRUE;
	}
	
	bool WindowsFilesys::mkDir(Path path)
	{
		bool success = resolve(path);
		if (!dirExsists(path) && success)
			success &= CreateDirectory(path, NULL) == TRUE;
		return success;
	}

	bool WindowsFilesys::mkFile(Path path)
	{
		resolve(path);
		HANDLE hfile = CreateFile(path, GENERIC_ALL, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		bool success = hfile != INVALID_HANDLE_VALUE;
		CloseHandle(hfile);
		return success;
	}

	bool WindowsFilesys::readfile(File& f)
	{
		return true;
		LPOFSTRUCT fileinfo;
		HFILE hf = OpenFile(f, fileinfo, OF_READ);
		LPVOID buffer;
	}

	bool WindowsFilesys::readTextFileToEnd(Path p, std::string& container)
	{
		FILE* file;
		resolve(p);
		fopen_s(&file, p, "rb");
		Burp<FILE*> fp(file, fclose);

		if (file == NULL)
			return false;
		fseek(file, 0, SEEK_END);
		container.resize(ftell(file));
		fseek(file, 0, SEEK_SET);
		fread(&container[0], sizeof(char), container.size(), file);
		fclose(file);
		return true;
	}

	bool WindowsFilesys::writeTextFile(Path p, std::string& content)
	{
		FILE* file;
		resolve(p);
		fopen_s(&file, p, "w");

		if (file == NULL)
			return false;
		
		Burp<FILE*> fp(file, fclose); // close on finallay
		fwrite(content.c_str(), sizeof(content[0]), content.size(), file);
		fclose(file);
		return true;
	}

	int ReadSourceFromFile(File& file)
	{
		FILE* fp = NULL;
		fopen_s(&fp, file, "rb");
		fseek(fp, 0, SEEK_END);
		file.size(ftell(fp));
		fseek(fp, 0, SEEK_SET);
		//fread(*source, 1, *sourceSize, fp);
		return 0;
	}


	bool WindowsFilesys::deleteFile(Path path)
	{
		resolve(path);
		return DeleteFile(path) == TRUE;
	}

	bool WindowsFilesys::isDirectory(Path path)
	{
		return PathIsDirectory(path);
	}

	bool WindowsFilesys::resolve(Path & path)
	{
		bool success = false;
		WCHAR resolved[MAX_PATH];
		memset(&resolved[0], NULL, MAX_PATH);
		DWORD len = ExpandEnvironmentStrings(path, &resolved[0], MAX_PATH);
		if (len > 0) {
			std::wstring resolvedStr(&resolved[0], &resolved[len]);
			path = resolvedStr;
		}
		return len > 0;
	}

	void WindowsFilesys::getFileInfo(File & file)
	{
		WIN32_FIND_DATA ffd;
		resolve(file);
		FindFirstFile(file, &ffd);

		file.size(ffd.nFileSizeLow >= 0
			? ffd.nFileSizeLow
			: (ffd.nFileSizeHigh * (MAXDWORD + 1)) + ffd.nFileSizeLow
		);
	}

	File WindowsFilesys::getFileInfo(Path path)
	{
		WIN32_FIND_DATA ffd;
		resolve(path);
		FindFirstFile(path, &ffd);
		File file(ffd.cFileName);
		file.size(ffd.nFileSizeLow >= 0 
			? ffd.nFileSizeLow 
			: (ffd.nFileSizeHigh * (MAXDWORD + 1)) + ffd.nFileSizeLow
		);
		return file;
	}

	std::vector<File> WindowsFilesys::lsFiles(Path dir)
	{
		WIN32_FIND_DATA ffd;
		std::vector<File> returnable;
		resolve(dir);
		if (!dirExsists(dir)) 
			return returnable;
		
		HANDLE hFind = FindFirstFile(dir.towstring().c_str(), &ffd);

		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
				returnable.push_back(File(VPath::Combine(dir.tostring(), ffd.cFileName), ffd.nFileSizeLow >= 0
					? ffd.nFileSizeLow
					: (ffd.nFileSizeHigh * (MAXDWORD + 1)) + ffd.nFileSizeLow)
				);
			while (FindNextFile(hFind, &ffd) != 0);
			FindClose(hFind);
		}
		return returnable;
	}

	std::string WindowsFilesys::platform()
	{
		return "Windows";
	}
}