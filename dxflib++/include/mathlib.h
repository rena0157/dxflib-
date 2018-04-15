#pragma once
#include "entities/point.h"
#include <cmath>

namespace dxflib
{
	namespace mathlib
	{
		// Constants
		constexpr static double pi{ 3.141592653589793 }; // The ratio between a circles diameter and its circumfrence

		// Misc Geometric Functions

		/**
		 * \brief Calculates the distance between vertex v0 to vertex v1 - Straight lines only
		 * \param v0 Starting Vertex
		 * \param v1 Ending Vertex
		 * \return The distance from V0 to V1
		 */
		inline double distance(const entities::vertex& v0, const entities::vertex& v1)
		{
			return sqrt(pow(v1.x - v0.x, 2) + pow(v1.y - v0.y, 2) + pow(v1.z - v0.z, 2));
		}
		/**
		 * \brief Calculates the distance between vertex v0 and vertex v1 - Bulge overload
		 * \param v0 Starting Vertex
		 * \param v1 Ending Vertex
		 * \param bulge The bulge defined by the arc segment
		 * \return The arc length from v0 to v1
		 */
		inline double distance(const entities::vertex& v0, const entities::vertex& v1, const double bulge)
		{
			return distance(v0, v1)/(2*sin(4*atan(bulge)/2))*4*atan(bulge);
		}

		/**
		 * \brief The area under a line that extends from v0 to v1. The area is from the line to the x-axis
		 * Note: The area will be negative if v0.x > v1.x
		 * \param v0 Starting Vertex
		 * \param v1 Ending Vertex
		 * \return The area under a line (v0, v1) to the x axis
		 */
		inline double trapz_area(const entities::vertex& v0, const entities::vertex& v1)
		{
			return v1.x - v0.x == 0 ? 0 : (v0.y + v1.y)*(v1.x - v0.x)/2;
		}

		inline double deg2_rad(const double deg) {return deg / 180 * pi;}

		inline double rad2_deg(const double rad) { return rad * 180 / pi; }

		class basic_vector
		{
		public:
			explicit basic_vector();
			explicit basic_vector(entities::vertex& v0, entities::vertex& v1);

			// Public interface
			const entities::vertex& operator[](int id) const;
			entities::vertex& operator[](int id);
			double magnitude() const { return distance(v0_, v1_); }

		private:
			entities::vertex v0_;
			entities::vertex v1_;
		};
	}
}
