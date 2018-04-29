#include "CppUnitTest.h"
#include "dxflib++/include/Cadfile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cadfile_test
{
	TEST_CLASS(cadfile_tests)
	{
	public:

		TEST_METHOD(load_filename)
		{
			try
			{
				dxflib::cadfile test{R"(C:\Dev\Test_DXF_files\load_filename_test.dxf)"};
			}
			catch (std::ios::failure&)
			{
				Assert::Fail(L"Exception (std::ios::failure) was raised");
			}
		}
	};
}
