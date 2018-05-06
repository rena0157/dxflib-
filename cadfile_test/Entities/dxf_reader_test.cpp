#include <CppUnitTest.h>
#include "dxflib++/include/reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cadfile_test
{
	TEST_CLASS(dxf_reader_tests)
	{
	public:
		TEST_METHOD(sentenial_test)
		{
			// Test for the sentenial. 

			dxflib::utilities::dxf_reader test_reader{
				R"(C:\Dev\Test_DXF_files\dxf_reader\sen_test.dxf)"
			};
			Assert::IsTrue(test_reader.is_binary());
		}
	};
}
