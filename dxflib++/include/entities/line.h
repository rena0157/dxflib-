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
			// Constructor
			explicit line(line_buf&);

			// public interface
			const vertex& get_vertex(int id) const;             // Returns the vertex given by it's id
			void move_vertex(int id, const vertex& new_vertex); // sets the vertex given by id to new location
			double get_thickness() const { return thickness_; } // Returns the thickness of the line

		private:
			// Properties
			vertex v0_;        // Starting Vertex
			vertex v1_;        // Ending Vertex
			double thickness_; // Thickness of the line
			double length_;    // distance from v0 to v1

			// Functions
			void recalculate_geometry() override;
		};
	}
	
}


