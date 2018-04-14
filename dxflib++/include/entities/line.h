#pragma once
#include "dxflib++/include/entities/entity.h"
#include "dxflib++/include/entities/point.h"

namespace dxflib
{
	namespace entities
	{
		/**
		* \brief Line buffer struct
		*/
		struct line_buf : entity_buffer_base
		{
			double x0, y0, z0;
			double x1, y1, z1;
			double thickness;

			/**
			 * \brief Parse function for line buffer
			 * \param cl Current Line
			 * \param nl Next Line
			 * \return Status 1:pass, 2: fail.
			 */
			int parse(const std::string& cl, const std::string& nl) override;
			/**
			 * \brief Frees memory and resets to defaults
			 */
			void free() override;
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
			double thickness;
			explicit line(line_buf&);
		};
	}
	
}


