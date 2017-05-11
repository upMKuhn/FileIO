#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace OpenCLFrameTests
{
	TEST_CLASS(VPath_Tests)
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

		TEST_METHOD(IsRoot_SlashHelloSlashWorld_ReturnsFalse)
		{
			VPath p("\\hello\\world");
			Assert::IsFalse(p.IsRoot());
		}

		TEST_METHOD(IsRoot_SlashHello_ReturnsFalse)
		{
			VPath p("\\hello");
			Assert::IsTrue(p.IsRoot());
		}

		TEST_METHOD(IsRoot_Slash_ReturnsTrue)
		{
			VPath p("\\");
			Assert::IsTrue(p.IsRoot());
		}

		TEST_METHOD(IsRoot_SlashHelloSlash_ReturnsTrue)
		{
			VPath p("\\hello\\");
			Assert::IsTrue(p.IsRoot());
		}

	};
}