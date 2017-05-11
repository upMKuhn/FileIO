#pragma once
#include <FileIO\FileIO.h>


namespace FileIO {
	
	class FILEIO_API Path {
	public: 
		Path() {}
		Path(std::string path) { setPath(path); };
		Path(const char* path) { setPath(path); };
		Path(const wchar_t* path) { setPath(std::wstring(path)); };


		operator const wchar_t*() { return m_wpath.data(); }
		operator const char*() { return m_path.data(); }
		operator std::string() { return m_path; }
		operator std::wstring() { return m_wpath; }
		friend bool operator==(const Path& lhs, const Path& rhs) { return lhs.m_path == rhs.m_path || lhs.m_wpath == rhs.m_wpath; }
		friend bool operator!=(const Path& lhs, const Path& rhs) { return lhs.m_path != rhs.m_path || lhs.m_wpath != rhs.m_wpath; }
		inline bool operator==(const Path& lhs) { return lhs.m_path == m_path || lhs.m_wpath == m_wpath;  }
		inline bool operator!=(const Path& lhs) { return lhs.m_path != m_path || lhs.m_wpath != m_wpath;}
		inline bool operator<(const Path& other) { return m_path.size() < other.m_path.size(); }
		inline void operator=(const Path& newdata) { setPath(newdata.m_path); }
		inline void operator=(const std::wstring& newdata) { setPath(newdata); }
		friend bool operator<(const Path& lhs, const Path& rhs) { return lhs.m_path.size() < rhs.m_path.size(); }
		bool equals(Path& other);

		Path& operator=(std::string data)
		{setPath(data); return *this;}

		virtual bool exsist();
		virtual bool empty() { return m_path.empty(); }
		bool isFile();
		std::string filename();
		std::string filenameWihtoutExtension();
		std::string fileExtension();
		
		///Remove Directory Name
		Path directory();
		std::string tostring() { return m_path; }
		std::wstring towstring() { return m_wpath; }

		virtual const char * c_str() { return m_path.c_str(); }
		virtual const wchar_t * wc_str() { return m_wpath.c_str(); }

		

		Path Combine(Path right) { setPath(Combine(m_path, right).m_path); return *this; }
		static Path Combine(Path left, Path right);

	protected: 
		virtual void setPath(std::string p);
		virtual void setPath(std::wstring p);
		

		std::string m_path;
		std::wstring m_wpath;

	};

}