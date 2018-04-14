#pragma once
#include "dxflib++/include/entities/point.h"
#include "entity.h"
#include <vector>
#include "dxflib++/include/utilities.h"

namespace dxflib
{
	namespace entities
	{
		/**
		 * \brief Geometric line segment
		 */
		class geoline
		{
		public:
			static constexpr int bulge_null{ -2 };
			/**
			 * \brief Geometric line segment to be used as base for lwpolyline
			 * \param v0 start vertex
			 * \param v1 end vertex
			 * \param bulge bulge value if arc segment
			 */
			explicit geoline(const vertex& v0, const vertex& v1, double bulge=bulge_null);

			vertex v0;
			vertex v1;
			double bulge;
			double length;
		};

		/**
		 * \brief AutoCAD LT 2013 group codes for the lwpoyline entity
		 */
		namespace group_codes
		{
			enum class lwpolyline
			{
				vertex_count = 90,
				polyline_flag = 70,
				elevation = 38,
				x_value = 10,
				y_value = 20,
				vertex_id = 91,
				bulge = 42,
				starting_width = 40,
				ending_width = 41,
				width = 43
			};
		}

		struct lwpolyline_buffer : entity_buffer_base
		{
			// Geometric Properties
			std::vector<double> x_values;
			std::vector<double> y_values;
			std::vector<double> bulge_values;
			// Other Properties
			bool polyline_flag{};
			double elevation{};
			int vertex_count{};
			double starting_width{};
			double ending_width{};
			double width{};


			// Parse function override
			int parse(const std::string& cl, const std::string& nl) override;
			void free() override;
		};

		class lwpolyline : public entity
		{
		public:
			// Properties
			int vertex_count;               // Total number of verticies in the polyline
			bool is_closed;                 // returns true if the polyline is closed
			double elevation;               // elevation of the polyline
			double starting_width;          // the starting global width 
			double ending_width;            // the ending global width
			double width;                   // the global width: only if starting width and ending width are 0
			std::vector<geoline> lines;     // the component lines of the polyline
			double length{};                  // total length of the polyline
			double area{};                    // Total area of the polyline

			// Constructors
			explicit lwpolyline(lwpolyline_buffer&);
			
			// Other
			void recalc_geometry() { calc_geometry(); };

		private:
			bool drawn_counter_clockwise_{};
			/**
			 * \brief Geoline binder takes vector of lines and creates a vector of geolines
			 * \param x X values vector
			 * \param y Y values vector
			 * \param bulge Bulge values
			 * \return a vector of geolines
			 */
			std::vector<geoline> geoline_binder(const std::vector<double>& x,
				const std::vector<double>& y, const std::vector<double>& bulge) const;

			/**
			 * \brief Function that calculates the total length & area of the polyline
			 */
			void calc_geometry();
		};
	}
}
