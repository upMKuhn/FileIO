#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace OpenCLFrameTests
{
	TEST_CLASS(Path_Tests)
	{
	public:
		
		MockFileSystem* mockfs;

		TEST_METHOD_INITIALIZE(ReCreateMocks)
		{
			mockfs = ((MockFileSystem*)FileSystem::get());
		}

		TEST_METHOD_CLEANUP(DeleteOldMock)
		{
			if (mockfs != nullptr) delete mockfs;
		}


		TEST_METHOD(directory_WhenFilePath_ReturnsDirPath)
		{
			Path p("C:\\Hello\\Test.txt");
			Path newPath = p.directory();
			Assert::AreEqual(string("C:\\Hello"), newPath.tostring());
		}

		TEST_METHOD(directory_WhenFileAtRoot_ReturnsRootSlash)
		{
			Path p("\\HelloWorld.txt");
			Path newPath = p.directory();
			Assert::AreEqual("\\", newPath.c_str());
		}

		TEST_METHOD(Construct_PathEndingSlash_TrailingSlashRemoved)
		{
			Path p("C:\\Hello\\Test\\");
			Assert::AreEqual(p.tostring(), string("C:\\Hello\\Test"));
		}

		TEST_METHOD(ConstructPath_WhenHasNoSlashes_ExpectNonEmpty)
		{
			Path p("Testfolder");
			Assert::AreEqual(string("Testfolder"), p.tostring());
		}

		TEST_METHOD(filename_FilePath_ReturnsFileNameWithExtension)
		{
			Path p("C:\\Hello\\Test.txt");
			Assert::AreEqual(p.filename(), string("Test.txt"));
		}

		TEST_METHOD(fileExtension_FilePath_ReturnsFileExtension)
		{
			Path p("C:\\Hello\\Test.txt");
			Assert::AreEqual(p.fileExtension(), string(".txt"));
		}

		TEST_METHOD(filename_DirPath_ReturnsNull)
		{
			Path p("C:\\Hello\\Test");
			Assert::AreEqual(string(""), p.filename());
		}

		
		TEST_METHOD(fileExtension_DirPath_ReturnsFileExtension)
		{
			Path p("C:\\Hello\\Test.txt");
			Assert::AreEqual(p.fileExtension(), string(".txt"));
		}

		TEST_METHOD(combine_withFileName_PathCombined)
		{
			Path p("C:\\test\\");
			p = p.Combine("test.txt");
			Assert::AreEqual("C:\\test\\test.txt", p);
		}

		TEST_METHOD(combine_withRelativePath_PathCombined)
		{
			Path p("C:\\test\\");
			p = p.Combine("subdir1\\subdir2");
			const char* expect = "C:\\test\\subdir1\\subdir2";
			Assert::AreEqual(expect, p);
		}

		TEST_METHOD(combine_withRelativePathStartWithSlash_PathCombined)
		{
			Path p("C:\\test\\");
			p = p.Combine("\\subdir1\\subdir2\\test.txt");
			const char* expect = "C:\\test\\subdir1\\subdir2\\test.txt";
			Assert::AreEqual(expect, p);
		}

		TEST_METHOD(combine_DirectoryPathWithFolderName_ReturnsAppendedFolderNameNoTrailingSlash)
		{
			Assert::AreEqual("\\test\\FolderName", Path("\\test").Combine("FolderName").c_str());
		}

		

	};
}