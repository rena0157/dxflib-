#include <CppUnitTest.h>
#include "dxflib++/include/Cadfile.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace entities_test
{
	TEST_CLASS(line_tests)
	{
	public:

		TEST_METHOD(parse_test)
		{
			dxflib::cadfile test{ R"(C:\Dev\Test_DXF_files\Line_tests\parse_test.dxf)" };
			const dxflib::entities::line& test_line = test.get_lines()[0];

			// Getting line from vector as a const ref
			Assert::IsTrue(&test_line == &test.get_lines()[0], L"Lines addresses not the same");

			// Points
			Assert::AreEqual(126.575982, test_line.get_vertex(0).x, 0.001, L"Parse Error: v0.x");
			Assert::AreEqual(251.158021, test_line.get_vertex(0).y, 0.001, L"Parse Error: v0.y");
			Assert::AreEqual(0.000, test_line.get_vertex(0).z, 0.001, L"Parse Error: v0.z");
			Assert::AreEqual(626.575982, test_line.get_vertex(1).x, 0.001, L"Parse Error: v1.x");
			Assert::AreEqual(251.158021, test_line.get_vertex(1).y, 0.001, L"Parse Error: v1.y");

			// Layer
			Assert::AreEqual("test_layer", test_line.get_layer().c_str());

			// Length
			Assert::AreEqual()
		}
	};
}
