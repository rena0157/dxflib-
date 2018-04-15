#pragma once
#include "entity.h"
#include "point.h"
#include "lwpolyline.h"

namespace dxflib
{
	namespace entities
	{
		namespace group_codes
		{
			enum class hatch
			{
				elevation_point_x = 10,
				elevation_point_y = 20,
				elevation_point_z = 30,
				hatch_pattern = 2,
				solid_fill_flag = 70,
				associativity_flag = 71,
				num_paths = 91,
				pattern_angle = 52,
				pattern_scale = 41,
				edge_type = 72
			};

			enum class boundary_path
			{
				// TODO: Need to finish this
			};
		}

		struct hatch_buffer : lwpolyline_buffer
		{
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
			int parse(const std::string& cl, const std::string& nl) override;
			void free() override;

		private:

		};

		class hatch : public entity
		{
		public:
			/**
			 * \brief Constructor using the hatch buffer created when the cadfile is
			 * constructed
			 * \param hb hatch buffer
			 */
			explicit hatch(hatch_buffer& hb);

			// General Properties
			vertex elevation;          // Elevation point of the hatch
			std::string hatch_pattern; // hatch pattern name
			bool is_solid;             // true if hatch is solid fill
			bool is_associative;       // true is the hatch has an associated lwpolyline
			int path_count;            // Number of boundary paths (loops)
			double pattern_angle;      // hatch pattern angle
			double pattern_scale;      // hatch pattern scale

			// Interfacing
			// Polyline pointer
			void set_lwpolyline(lwpolyline* in) { polyline_ptr_ = in; }
			lwpolyline* get_lwpolyline() const { return polyline_ptr_; }

			// Geometric
			double area() const { return polyline_ptr_ == nullptr ? area_ : polyline_ptr_->get_area(); }
			double perimeter() const { return polyline_ptr_ == nullptr ? area_ : polyline_ptr_->get_length(); }

		private:
			double area_{};
			double perimeter_{};
			lwpolyline * polyline_ptr_{nullptr};
			std::vector<geoline> geolines_;
			void calc_geometry();
		};
	}
}
