#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FileIO::Common;

namespace OpenCLFrameTests
{

	TEST_CLASS(VFS_Tests)
	{
	public:
		const char * BASE_DIR = "C:\\unitTests\\";
		const wchar_t * L_BASE_DIR = L"C:\\unitTests";
		const char * SUB_BASE_DIR = "C:\\unitTests\\subDir";

		BurpPointer<FileSystem*> fs;
		MockFileSystem* mockfs;

		TEST_METHOD_INITIALIZE(VFS_Tests_INIT)
		{
			FileSystem::setMode(FileSystem::FS_MODE_MEMORY);
			mockfs = ((MockFileSystem*)FileSystem::get());
			mockfs->mkDir(BASE_DIR);
			mockfs->mkDir(SUB_BASE_DIR);
			fs = FileSystem::get();
		}

		TEST_METHOD_CLEANUP(VFS_Tests_DONE) {
			mockfs->reset();
		}


		TEST_METHOD(Mount_DirectoryOneToOne_ReturnsCorrectPhysicalPath)
		{
			Path EXPECTED_PATH = Path(BASE_DIR);
			VPath virtualPath("\\temp");
			VFS& vfs = *VFS::Get();

			vfs.Mount("\\temp", BASE_DIR);
			const char* resolvedPath = vfs.Resolve("\\temp").c_str();
			Assert::AreEqual(L_BASE_DIR, vfs.Resolve("\\temp").wc_str());
		}

		TEST_METHOD(Resolve_whenInvalid_ReturnsInput)
		{
			VPath virtualPath("\\invalid\\VPath");
			VFS& vfs = *VFS::Get();
			vfs.Mount("\\temp", BASE_DIR);

			Assert::AreEqual(L"\\invalid\\VirtualPath", vfs.Resolve("\\invalid\\VirtualPath\\").wc_str());
		}

		TEST_METHOD(Mount_OneVirtualPathToMultiplePhysicalPaths_CanResolveToBothPhysicalPaths)
		{
			Path EXPECTED_PATH = Path(BASE_DIR);
			VPath virtualPath("\\temp");
			VFS& vfs = *VFS::Get();

			//mount the two directories
			vfs.Mount("\\temp", BASE_DIR);
			vfs.Mount("\\temp", SUB_BASE_DIR);
			
			//fake directories to check later both paths has been maped
			Path PathOne(BASE_DIR);
			mockfs->mkDir(PathOne.Combine("PathOne"));
			Path PathTwo(SUB_BASE_DIR);
			mockfs->mkDir(PathTwo.Combine("PathTwo"));

			Assert::AreEqual(PathOne.wc_str(), vfs.Resolve("\\temp\\PathOne").wc_str());
			Assert::AreEqual(PathTwo.wc_str(), vfs.Resolve("\\temp\\PathTwo").wc_str());
		}


		TEST_METHOD(Resolve_VPathForFile_ReturnsPhysicalFilePath)
		{
			Path EXPECTED_FILE = Path::Combine(BASE_DIR, "temp.tmp");
			fs->mkFile(EXPECTED_FILE);

			VFS& vfs = *VFS::Get();
			vfs.Mount("\\temp", BASE_DIR);
			Assert::AreEqual(EXPECTED_FILE.wc_str(), vfs.Resolve("\\temp\\temp.tmp").wc_str());
		}

		TEST_METHOD(exsits_implemented) {
			VFS::exsists(BASE_DIR);
			Assert::IsTrue(true);
		}

	};
}