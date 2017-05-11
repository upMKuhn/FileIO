#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OpenCLFrameTests
{

	TEST_CLASS(TextFileTests)
	{
	public:
		const char * BASE_VDIR = "\\VDir\\";
		const char * BASE_DIR = "%temp%\\unitTests\\";
		const char*	 TEST_FILE = "%temp%\\unitTests\\readToEnd.txt";
		const char*	 VTEST_FILE = "\\VDir\\readToEnd.txt";

		Path filePath;
		MockFileSystem* mockfs;
		TEST_METHOD_INITIALIZE(ReCreateMocks)
		{
			mockfs = ((MockFileSystem*)FileSystem::get());
			mockfs->mkDir(BASE_DIR);
			VFS::Get()->Mount(BASE_VDIR, BASE_DIR);
			filePath = Path::Combine(BASE_DIR, "temp.tmp");
		}

		TEST_METHOD_CLEANUP(TextFileTests_Cleanup) {
			mockfs->reset();
		}
		
		TEST_METHOD(TextFileCast_ToCString_ReturnsContent)
		{
			const char* TEXT_CONTENT = "HELLO WORLD!";
			mockfs->MockTextFile(TEST_FILE,TEXT_CONTENT);

			TextFile tfile(VTEST_FILE);
			tfile.ReadToEnd();
			const char* content = tfile;
			Assert::IsTrue(strcmp(TEXT_CONTENT, content));
		}

		TEST_METHOD(TextFileCast_WhenAsFilePointer_ReturnsFilePath)
		{
			const char* TEXT_CONTENT = "HELLO WORLD!";
			mockfs->MockTextFile(TEST_FILE, TEXT_CONTENT);

			TextFile tfile(VTEST_FILE);
			tfile.ReadToEnd();
			File* file = &tfile;
			Assert::AreEqual(VTEST_FILE, *file);
		}

	};
}