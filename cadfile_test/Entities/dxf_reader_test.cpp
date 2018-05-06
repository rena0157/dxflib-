#include <CppUnitTest.h>
#include "dxflib++/include/reader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace cadfile_test
{
	TEST_CLASS(dxf_reader_tests)
	{
	public:
		TEST_METHOD(bin_sentenial)
		{
			// Test for the sentenial. 
			dxflib::utilities::dxf_reader test_reader{
				R"(C:\Dev\Test_DXF_files\dxf_reader\sen_test_bin.dxf)"
			};
			// if the sentenial is found then return true
			Assert::IsTrue(test_reader.is_binary());
			Assert::AreEqual(test_reader.get_file_size(), 64793);
		}

		TEST_METHOD(ascii_sentenial)
		{
			dxflib::utilities::dxf_reader test_reader{
				R"(C:\Dev\Test_DXF_files\dxf_reader\sen_test_ascii.dxf)"
			};
			Assert::IsFalse(test_reader.is_binary());
			Assert::AreEqual(test_reader.get_file_size(), 125567);
		}
	};
}
