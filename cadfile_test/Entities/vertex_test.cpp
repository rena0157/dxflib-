#include <CppUnitTest.h>
#include "dxflib++/include/Cadfile.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace entity_tests
{
	TEST_CLASS(vertex)
	{
	public:
		TEST_METHOD(get_vertex)
		{
			const dxflib::entities::vertex test_vertex{ 2.3, 5.2, 3.1 };
			Assert::AreEqual(2.3, test_vertex.x, 0.1);
			Assert::AreEqual(5.2, test_vertex.y, 0.1);
			Assert::AreEqual(3.1, test_vertex.z, 0.1);
		}

		TEST_METHOD(within)
		{
			dxflib::cadfile c_file{ R"(C:\Dev\Test_DXF_files\vertex\within.dxf)" };
			
			// With polyline
			dxflib::entities::vertex vertex{ 4, 3.3 };
			Assert::IsTrue(vertex.within(c_file.get_lwpolylines()[0]));

			// with geoline
			Assert::IsTrue(vertex.within(c_file.get_lwpolylines()[0].get_lines()));
		}

		TEST_METHOD(within_arc)
		{
			dxflib::cadfile c_file{ R"(C:\Dev\Test_DXF_files\vertex\within_arc.dxf)" };

			// With polyline - fails because the vertex is within an arc segment
			dxflib::entities::vertex vertex{ 2.5, 3.7 };
			Assert::IsTrue(vertex.within(c_file.get_lwpolylines()[0]), L"pl failure");

			// with geoline
			Assert::IsTrue(vertex.within(c_file.get_lwpolylines()[0].get_lines()), L"geoline failure");
		}
	};
}
