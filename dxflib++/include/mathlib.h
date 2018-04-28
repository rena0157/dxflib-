#pragma once
/*
 * dxflib++
 * mathlib.h
 * Purpose: To contain the prototypes of functions pertaining to mathematical utilities
 *			that are used in the dxflib library
 * 
 * Author: Adam Renaud
 */
#include "entities/point.h"
#include <vector>
#include <cmath>

// Predeclareation of geolines
namespace dxflib::entities
{
	class geoline;
	class lwpolyline;
}

namespace dxflib::mathlib
{
	// Constants
	constexpr static double pi{3.141592653589793}; // The ratio between a circles diameter and its circumfrence

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
		return distance(v0, v1) / (2 * sin(4 * atan(bulge) / 2)) * 4 * atan(bulge);
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
		return v1.x - v0.x == 0 ? 0 : (v0.y + v1.y) * (v1.x - v0.x) / 2;
	}

	/**
	 * \brief Converts degrees to radians
	 * \param deg angle to convert from degrees to radians
	 * \return angle in radians
	 */
	inline double deg2_rad(const double deg) { return deg / 180 * pi; }

	/**
	 * \brief Converts radians to degrees
	 * \param rad angle to convert from radians to degrees
	 * \return angle in degrees
	 */
	inline double rad2_deg(const double rad) { return rad * 180 / pi; }

	/**
	 * \brief Calculates the area between an arc segment and a line that extends from
	 * the starting vertex of the arc to the ending vertex of the arc. Note: total_angle
	 * must be in radians
	 * \param radius Radius of the arc
	 * \param total_angle angle between both legs of the arc
	 * \return area of the arc segment
	 */
	inline double chord_area(const double radius, const double total_angle)
	{
		return std::pow(radius, 2.0) / 2 * (total_angle - std::sin(total_angle));
	}

	namespace exceptions
	{
		class no_associated_vertex : public std::exception
		{
			std::string message_;
		public:
			explicit no_associated_vertex(const char* message): message_(message)
			{
			}

			char const* what() const override { return message_.c_str(); }
		};
	}

	/**
	 * \brief Vector Base class
	 */
	class basic_vector
	{
	public:
		explicit basic_vector(const entities::vertex& v0, const entities::vertex& v1);
		explicit basic_vector(double x, double y, double z);
		explicit basic_vector(const entities::geoline& gl);

		// Public interface

		/*
		 * Vertex Reference operators.
		 * Returns a reference either const or not to a vertex that is a member of the vector
		 * This function can fail if is_free() is false: it will throw a no associated vertex exception
		 */
		const entities::vertex& operator[](int id) const;
		entities::vertex& operator[](int id);

		// Geometric Properties
		double magnitude() const; // Returns the magnitude of the vector
		double x() const { return x_; } // Returns the x component
		double y() const { return y_; } // Returns the y component
		double z() const { return z_; } // Returns the z component
		bool is_free() const { return has_verticies_; } // Returns true if vector is associated with verticies

		// Mathematical Operations
		inline basic_vector operator+(const basic_vector& v) const; // Returns a sum of vectors
		inline basic_vector operator-(const basic_vector& v) const; // Returns a subtraction of vectors

		/**
		 * \brief The dot product function
		 * \param v0 vector 1
		 * \param v1 vector 2
		 * \return the dot product of vector 1 and vector 2
		 */
		static double dot_product(const basic_vector& v0, const basic_vector& v1);

		/**
		 * \brief The vector cross product function
		 * Note: This will return a free vector (This vector will not be associated with
		 * any verticies)
		 * \param v0 vector 1 
		 * \param v1 vector 2
		 * \return a vector that is the resultant of v0 cross v1
		 */
		static basic_vector cross_product(const basic_vector& v0, const basic_vector& v1);

		// Ostream Overload
		friend std::ostream& operator<<(std::ostream& os, const basic_vector& bv);

	private:
		entities::vertex v0_;
		entities::vertex v1_;
		double x_;
		double y_;
		double z_;
		bool has_verticies_;
	};

	int winding_num(const std::vector<entities::geoline>& geolines, const entities::vertex& v);
}
