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

	// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
	/**
	 * \brief ARC entity 
	 */
	class arc : entity
	{
	public:
		// Constructor
		explicit arc(arc_buffer& ab);

		// Public Interface
		// Get
		const vertex& get_center_point() const { return center_point_; }     // Returns the Center Point
		const vertex& get_start_point() const { return start_point_; }       // Returns the Start Point
		const vertex& get_end_point() const { return end_point_; }           // Returns the End Point
		double get_radius() const { return radius_; }                        // Returns the Radius
		double get_thickness() const { return thickness_; }                  // Returns the Thickness
		double get_start_angle() const { return start_angle_; }              // Returns the Starting Angle
		double get_end_angle() const { return end_angle_; }                  // Returns the Final Angle
		double get_total_angle() const { return end_angle_ - start_angle_; } // Returns the Final Angle - Starting Angle

	private:
		// Properties
		vertex center_point_; // Center point of the arc
		vertex start_point_;  // Starting point of the arc
		vertex end_point_;    // ending point of the arc
		double radius_;       // radius of the arc
		double thickness_;    // thickness of the line that is the arc
		double start_angle_;  // starting angle in degrees
		double end_angle_;    // ending angle in degrees

		void calc_other_points();
	};
}


