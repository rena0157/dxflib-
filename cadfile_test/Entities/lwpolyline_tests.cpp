#include "dxflib++/include/Cadfile.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(lwpolyline)
{
	TEST_METHOD(within_test)
	{
		dxflib::cadfile c_file{ R"(C:\Dev\Test_DXF_files\lwpolyline\within_test.dxf)" };

		for (const auto& pl : c_file.get_lwpolylines())
			for (const auto& t : c_file.get_text())
				Assert::IsTrue(t.first_alignment().within(pl),
					std::wstring{t.get_string().begin(), t.get_string().end()}.c_str());
	}
};