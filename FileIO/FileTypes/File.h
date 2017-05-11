#pragma once
namespace FileIO {
	#include <FileIO\FileTypes\FileTypes.h>
	#include <streambuf>
	class VPath;
	class FILEIO_API File : public VPath
	{
	public:
		File() {};
		File(VPath path) : VPath(path) {}
		File(std::string path) : VPath(path) {};
		File(const char* path) : VPath(path) {};
		File(VPath path, uint64_t fileLen) : VPath(path) { size(fileLen); }
		File(std::string path, uint64_t fileLen) : VPath(path) { size(fileLen); }
		File(const char* path, uint64_t fileLen) : VPath(path) { size(fileLen); }
		~File();
	
		inline bool operator==(const File& lhs) { return lhs.m_path == m_path || lhs.m_wpath == m_wpath; }
		inline bool operator!=(const File& lhs) { return lhs.m_path != m_path || lhs.m_wpath != m_wpath; }
		friend bool operator==(const File& lhs, const File& rhs) { return lhs.m_path == rhs.m_path || lhs.m_wpath == rhs.m_wpath; }
		friend bool operator!=(const File& lhs, const File& rhs) { return lhs.m_path != rhs.m_path || lhs.m_wpath != rhs.m_wpath; }

		operator const wchar_t*();
		operator const char*();
		operator std::string();
		operator std::wstring();

		inline void size(uint64_t s) { this->f_length = s;}
		virtual uint64_t size();
		
		FlushOption flushoption = FLUSH_MANUAL;
	private:
		uint64_t f_length = UINT64_MAX;
	};

}



