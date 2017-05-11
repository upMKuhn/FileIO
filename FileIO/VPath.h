#pragma once
#include <FileIO\FileIO.h>

namespace FileIO {

	//Virtual Path
	class FILEIO_API VPath : public Path
	{
	public:
		VPath() {}
		VPath(std::string path) : Path(path) { setPath(path); }
		VPath(const char* path) : Path(path) { setPath(path); }
		VPath(const wchar_t* path) : Path(path) { setPath(m_path); } //the base constructor sets mPath...


		inline bool operator<(const VPath& other) { return m_path.size() < other.m_path.size(); }
		inline bool operator==(const VPath& p) { return p.m_path == this->m_path; }
		inline bool operator!=(const VPath& p) { return p.m_path != this->m_path; }

		bool exsist() override;
		VPath dotdot();

		VPath Combine(VPath right) { setPath(Combine(m_path, right.tostring()).tostring()); return *this; }
		static VPath Combine(VPath left, VPath right);

		bool inline IsRoot() { return m_root; }
	protected:
		Path resolvePath();

		void setPath(std::string path) override;

	private:
		bool m_root;
		
	};


}