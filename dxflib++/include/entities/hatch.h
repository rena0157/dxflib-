#pragma once
#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/entities/point.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include "dxflib++/include/entities/arc.h"

namespace dxflib::entities
{
	namespace group_codes
	{
		enum class hatch
		{
			elevation_point_x = 10,
			elevation_point_y = 20,
			elevation_point_z = 30,
			hatch_pattern = 2,
			solid_fill_color = 63,
			solid_fill_flag = 70,
			associativity_flag = 71,
			num_paths = 91,
			hatch_style = 75,
			hatch_pattern_type = 76,
			pattern_angle = 52,
			pattern_scale = 41,
			pattern_line_count = 78,
			edge_type = 72,
			edge_count = 93,
			seed_count = 98,
			offset_vector = 11,
			pass1 = 1070,
			// Ignore do to conflict
		};

		enum class boundary_paths
		{
			line = 1,
			circular_arc = 2,
			eliptical_arc = 3,
			spline = 4
		};

		enum class line_path
		{
			starting_point_x = 10,
			ending_point_x = 11,
			starting_point_y = 20,
			ending_point_y = 21
		};
	}

	struct hatch_buffer : lwpolyline_buffer, arc_buffer
	{
		constexpr static int null_edge_type{-1};
		int edge_type{null_edge_type};
		// Properties
		double elevation_point_x{};
		double elevation_point_y{};
		double elevation_point_z{};
		std::string hatch_pattern{};
		bool is_solid{};
		bool is_associative{};
		int path_count{};
		double pattern_angle{};
		double pattern_scale{};

		// Functions
		int parse(const std::string& cl, const std::string& nl) override; // Parse override 
		void free() override;
	};

	namespace exceptions
	{
		/**
		 * \brief Exception that is called when there is no associated lwpolyline with a hatch
		 */
		struct no_associated_lwpolyline : std::exception
		{
			explicit no_associated_lwpolyline(std::string error);
			const char* what() const override { return error_.c_str(); }
		private:
			std::string error_;
		};
	}

	// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
	class hatch : public entity
	{
	public:
		/**
		 * \brief Constructor using the hatch buffer created when the cadfile is
		 * constructed
		 * \param hb hatch buffer
		 */
		explicit hatch(hatch_buffer& hb);

		// Public Interface
		// Get
		const lwpolyline* get_lwpolyline() const; // Returns the pointer to a lwpolyline
		double get_area() const; // Returns the area of the hatch
		double get_perimeter() const; // Returns the Perimeter of the hatch
		const vertex& get_elevation_point() const { return elevation_; } // Returns the elevation of the hatch
		const std::string& get_hatch_pattern() const { return hatch_pattern_; } // Returns the hatch pattern name
		bool is_solid() const { return is_solid_; } // Returns true if the hatch pattern is solid
		bool is_associated() const { return is_associative_; } // Returns true if the hatch has an associated lwpolyline
		int path_count() const { return path_count_; } // Returns the number of paths that are associated with the hatch
		double get_pattern_angle() const { return pattern_angle_; } // Returns the hatch pattern angle (Must be !solid)
		double get_pattern_scale() const { return pattern_scale_; } // Returns the hatch patter scale (Must be !solid) 
		// Set
		void set_lwpolyline(lwpolyline* in) { polyline_ptr_ = in; } // Sets the lwpolyline pointer of the hatch
		// Other functions
		bool within(const vertex& v) const; // Returns True if v is in hatch

	private:
		// Members
		// General Properties
		vertex elevation_; // Elevation point of the hatch
		std::string hatch_pattern_; // hatch pattern name
		bool is_solid_; // true if hatch is solid fill
		bool is_associative_; // true is the hatch has an associated lwpolyline
		int path_count_; // Number of boundary paths (loops)
		double pattern_angle_; // hatch pattern angle
		double pattern_scale_; // hatch pattern scale
		double area_{}; // Area of the hatch
		double perimeter_{}; // Perimeter of the hatch
		lwpolyline* polyline_ptr_{nullptr}; // Pointer to a lwpolyline
		std::vector<geoline> geolines_; // geolines that are constructed if there is not lwpolyline* found
		void calc_geometry(); // Calculate the area and perimeter
	};
}
