#pragma once
#include <vector>

namespace dxflib::entities
{
	/**
	* \brief point base class
	*/
	class point_base
	{
	public:
		double x, y, z;
		explicit point_base(double x = 0, double y = 0, double z = 0);
		friend std::ostream& operator<<(std::ostream& os, point_base pb);
	};

	/**
	* \brief Vertex Class
	*/
	class vertex : public point_base
	{
	public:
		/**
		* \brief Vertex Object is a sinlge point defined by: x, y, z
		* \param x x position
		* \param y y position
		* \param z z position
		*/
		explicit vertex(double x = 0, double y = 0, double z = 0);
	};
}
