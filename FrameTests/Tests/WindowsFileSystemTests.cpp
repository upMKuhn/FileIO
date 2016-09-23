#include "stdafx.h"
#include "CppUnitTest.h"


namespace OpenCLFrameTests
{
	const char * const TEST_FILES[] = { "test.txt", "tobeDelted.txt", "readFile.txt", "writeFile.txt" };
	const char * const BASE_DIR = "%temp%\\unitTests\\";

	///IO should not be testes ..... 
	///well this stuff is to complicated not to test it!
	TEST_CLASS(WindowsFileSystemTests_IO_UNIT_TEST)
	{
	public:
		static Common::Burp<FileSystem*> fs;



		TEST_CLASS_INITIALIZE(setup)
		{
			fs = new WindowsFilesys();
			fs->mkDir(BASE_DIR);
			for (int i = 0; i < ARRAYSIZE(TEST_FILES); i++)
				fs->deleteFile(Path::Combine(BASE_DIR, TEST_FILES[i]));
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			fs->mkDir(BASE_DIR);
			for (int i = 0; i < ARRAYSIZE(TEST_FILES); i++)
				fs->deleteFile(Path::Combine(BASE_DIR, TEST_FILES[i]));
		}

		TEST_METHOD(getFilesystem_ReturnsPlatformSpecificObj)
		{
			Assert::AreEqual(string("Windows"), fs->platform());
		}

		TEST_METHOD(mkDir_withValidPath_CreatesDirectory)
		{
			Path path(BASE_DIR);

			//Note I am checking here 2 things 1. dir created and 
			//2. dirExsists function resolves path 
			Assert::IsTrue(fs->dirExsists(path));
		}

		TEST_METHOD(mkFile_withValidPath_CreatesFile)
		{
			Path path(BASE_DIR);
			bool operationPassed = fs->mkFile(path.Combine(TEST_FILES[0]));
			bool fileExsists = fs->fileExsists(path);
			Assert::IsTrue(operationPassed && fileExsists);
		}

		TEST_METHOD(deleteFile_validPath_FileDeleted)
		{
			Path path(BASE_DIR);
			fs->mkFile(path.Combine(TEST_FILES[1]));
			fs->fileExsists(path);
			Assert::IsTrue(fs->fileExsists(path));
			fs->deleteFile(path);
			Assert::IsFalse(fs->fileExsists(path));
		}

		TEST_METHOD(deleteFile_invalidPath_ReturnsFalse)
		{
			Path path(BASE_DIR);
			path.Combine("randomFile.rnd");
			Assert::IsFalse(fs->fileExsists(path));
			Assert::IsFalse(fs->deleteFile(path));
			Assert::IsFalse(fs->fileExsists(path));
		}

		TEST_METHOD(resolve_EnviormentVariables_ReturnsAbsolutPath)
		{
			Path EnviormentVar = "%ProgramData%\\dir";
			const char* EXPANDED_PATH = "C:\\ProgramData\\dir";
			fs->resolve(EnviormentVar);
			Assert::AreEqual(EXPANDED_PATH, EnviormentVar);
		}
		
		TEST_METHOD(ReadTextFileToEnd_ValidPath_ContentCorrect)
		{
			Path file = Path::Combine(BASE_DIR, TEST_FILES[2]);
			const char * FILE_CONTENT = "Hello world !_*!";
			//create File to read....
			fs->writeTextFile(file, string(FILE_CONTENT));

			string container;
			fs->readTextFileToEnd(file, container);
			Assert::AreEqual(FILE_CONTENT, container.c_str());
		}
	};

	Common::Burp<FileSystem*> WindowsFileSystemTests_IO_UNIT_TEST::fs;
}