#pragma once
#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/entities/point.h"

namespace dxflib
{
	/**
	 * \brief Line buffer struct
	 */
	struct line_buf : entity_buffer_base
	{
		double x0, y0, z0;
		double x1, y1, z1;
		int parse(const std::string& cl, const std::string& nl) override;
	};

	namespace group_codes
	{
		enum class line_codes
		{
			subclassmarker = 100,
			error = -1,
			thickness = 39,
			x0 = 10, x1 = 11,
			y0 = 20, y1 = 21,
			z0 = 30, z1 = 31,
		};
	}

	/**
	 * \brief Line Entity
	 */
	class line : public entity
	{
	public:
		vertex v0;
		vertex v1;
		explicit line(line_buf&);
	};
}


