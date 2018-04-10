#pragma once
#include "dxflib++/include/entities/point.h"
#include "entity.h"
#include <vector>

namespace dxflib
{
	namespace entities
	{
		/**
		 * \brief Geometric line segment
		 */
		class geo_line
		{
		public:

			/**
			 * \brief Geometric line segment to be used as base for lwpolyline
			 * \param v0 start vertex
			 * \param v1 end vertex
			 * \param bulge bulge value if arc segment
			 */
			explicit geo_line(const vertex& v0, const vertex& v1, double bulge=0);

			vertex v0;
			vertex v1;
			double bulge;
			double length;
		};

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
				bulge = 42
			};
		}

		struct lwpolyline_buffer : entity_buffer_base
		{
			// Properties
			std::vector<double> x_values;
			std::vector<double> y_values;
			bool polyline_flag;
			double elevation;
			int vertex_count;

			// Parse function override
			int parse(const std::string& cl, const std::string& nl) override;
		};

		class lwpolyline : public entity
		{
		public:
			explicit lwpolyline(lwpolyline_buffer&);
		};
	}
}
