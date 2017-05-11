#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FileIO::Common;

namespace OpenCLFrameTests
{

	TEST_CLASS(VFS_Tests)
	{
	public:
		const char * BASE_DIR = "%temp%\\unitTests\\";
		const char * SUB_BASE_DIR = "%temp%\\unitTests\\subDir\\";

		Burp<FileSystem*> fs;
		MockFileSystem* mockfs;

		TEST_METHOD_INITIALIZE(ReCreateMocks)
		{
			mockfs = ((MockFileSystem*)FileSystem::get());

			mockfs->mkDir(BASE_DIR);
			mockfs->mkDir(SUB_BASE_DIR);
			fs = FileSystem::get();
		}

		TEST_METHOD(Mount_DirectoryOneToOne_ReturnsCorrectPhysicalPath)
		{
			Path EXPECTED_PATH = Path(BASE_DIR);
			VPath virtualPath("\\temp");
			VFS& vfs = *VFS::Get();

			vfs.Mount("\\temp", BASE_DIR);
			Assert::AreEqual(Path(BASE_DIR).c_str() ,vfs.Resolve("\\temp").c_str());
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

			Assert::AreEqual(PathOne.c_str(), vfs.Resolve("\\temp\\PathOne").c_str());
			Assert::AreEqual(PathTwo.c_str(), vfs.Resolve("\\temp\\PathTwo").c_str());
		}


		TEST_METHOD(Resolve_VPathForFile_ReturnsPhysicalFilePath)
		{
			Path EXPECTED_FILE = Path::Combine(BASE_DIR, "temp.tmp");
			fs->mkFile(EXPECTED_FILE);

			VFS& vfs = *VFS::Get();
			vfs.Mount("\\temp", BASE_DIR);
			Assert::IsTrue(EXPECTED_FILE == vfs.Resolve("\\temp\\temp.tmp"));
		}

	};
}