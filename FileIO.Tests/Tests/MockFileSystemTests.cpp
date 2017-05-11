#include "stdafx.h"
#include "CppUnitTest.h"


namespace OpenCLFrameTests
{
	const char * const TEST_FILES[] = { "test.txt", "tobeDelted.txt" };
	const char *  const BASE_DIR = "%temp%\\unitTests\\";

	///IO should not be testes ..... 
	///well this stuff is to complicated not to test it!
	TEST_CLASS(MockFileSystemTests_IO_UNIT_TEST)
	{
	public:
		static FileSystem* UNDER_TEST;
		static MockFileSystem mockHelper;

		TEST_CLASS_INITIALIZE(setup)
		{
			UNDER_TEST = &mockHelper;
			mockHelper.mkDir(BASE_DIR);
			
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			for (int i = 0; i < ARRAYSIZE(TEST_FILES); i++)
				mockHelper.deleteFile(Path::Combine(BASE_DIR, TEST_FILES[i]));
		}

		TEST_METHOD(getFilesystem_ReturnsPlatformSpecificObj)
		{
			Assert::AreEqual(string("Mock"), UNDER_TEST->platform());
		}

		TEST_METHOD(mkDir_withValidPath_CreatesDirectory)
		{
			Path path(BASE_DIR);

			//Note I am checking here 2 things 1. dir created and 
			//2. dirExsists function resolves path 
			Assert::IsTrue(UNDER_TEST->dirExsists(path));
		}

		TEST_METHOD(mkFile_withValidPath_CreatesFile)
		{
			Path path(BASE_DIR);
			bool operationPassed = UNDER_TEST->mkFile(path.Combine(TEST_FILES[0]));
			bool fileExsists = UNDER_TEST->fileExsists(path);
			Assert::IsTrue(operationPassed && fileExsists);
		}

		TEST_METHOD(deleteFile_validPath_FileDeleted)
		{
			Path path(BASE_DIR);
			mockHelper.mkFile(path.Combine(TEST_FILES[1]));
			mockHelper.fileExsists(path);
			UNDER_TEST->deleteFile(path);
			Assert::IsFalse(UNDER_TEST->fileExsists(path));
		}

		TEST_METHOD(ReadTextFileToEnd_ValidPath_ReturnsContent)
		{
			const char* FILE_CONTENT = "WOW HELLO I AM A FILE";
			string filecontent;
			Path filePath = Path::Combine(BASE_DIR, "Test.txt");
			mockHelper.MockTextFile(filePath, FILE_CONTENT);
			
			
			UNDER_TEST->readTextFileToEnd(filePath, filecontent);
			Assert::AreEqual(FILE_CONTENT, filecontent.c_str());
		}

		TEST_METHOD(WriteTextFile_ValidPath_ReturnsContent)
		{
			const char* FILE_CONTENT = "WOW HELLO I AM A FILE";
			string filecontent = FILE_CONTENT;
			Path filePath = Path::Combine(BASE_DIR, "Test.txt");

			UNDER_TEST->writeTextFile(filePath, filecontent);
			Assert::AreEqual(FILE_CONTENT, mockHelper.fileContent[filePath].c_str());
		}

	};

	FileSystem* MockFileSystemTests_IO_UNIT_TEST::UNDER_TEST;
	MockFileSystem MockFileSystemTests_IO_UNIT_TEST::mockHelper;



}