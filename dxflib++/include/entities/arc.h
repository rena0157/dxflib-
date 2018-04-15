#pragma once
#include "dxflib++/include/entities/point.h"
#include "dxflib++/include/entities/entity.h"

namespace dxflib::entities
{
	namespace group_codes
	{
		enum class arc
		{
			thickness = 39,
			center_point_x = 10,
			center_point_y = 20,
			center_point_z = 30,
			radius = 40,
			start_angle = 50,
			end_angle = 51
		};
	}
	struct arc_buffer : entity_buffer_base
	{
		double center_point_x{};
		double center_point_y{};
		double center_point_z{};
		double thickness{};
		double radius{};
		double start_angle{};
		double end_angle{};
		int parse(const std::string& cl, const std::string& nl) override;
		void free() override;
	};

	class arc : entity
	{
	public:
		// Constructor
		explicit arc(arc_buffer& ab);

		// Properties
		vertex center_point;          // Center point of the arc
		vertex start_point;           // Starting point of the arc
		vertex end_point;             // ending point of the arc
		double radius;                // radius of the arc
		double thickness;             // thickness of the line that is the arc
		double start_angle;           // starting angle in degrees
		double end_angle;             // ending angle in degrees
		double total_angle;           // total angle = ending angle - starting angle

	private:
		void calc_other_points();
	};
}


