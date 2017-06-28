#pragma once
#include "FileTypes.h"
namespace FileIO {
	class FILEIO_API TextFile : public File
	{
	public:
		TextFile();
		TextFile(VPath path) : File(path) {}
		//TextFile(std::string path) : File(path) {};
		//TextFile(const char* path) : File(path) {};
		TextFile(VPath path, uint64_t fileLen) : File(path, fileLen) {}
		TextFile(std::string path, uint64_t fileLen) : File(path, fileLen) {}
		TextFile(const char* path, uint64_t fileLen) : File(path, fileLen) {}

		~TextFile();

		bool ReadToEnd();

		bool Save();

		friend std::istream& operator>> (std::istream& in, const TextFile& x)
		{ 
			std::streamsize s = in.gcount();
			return in;
		}

		friend std::ostream& operator<< (std::ostream& out, const TextFile& x)
		{
			return out;
		}

		const char * c_str() override { return m_fcontent.c_str(); }

		
		operator const char*() { return m_fcontent.c_str(); }

		operator const char**() { return (const char **)m_fcontent.c_str(); }

		uint64_t size() override;

	private:
		bool m_reachedEndofFile = false;
		void setContentSize(size_t size) { m_fcontent.resize(size); };
		std::string m_fcontent;
	};
}
