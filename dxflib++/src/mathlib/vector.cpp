#include "dxflib++/include/mathlib.h"
#include "dxflib++/include/entities/lwpolyline.h"

dxflib::mathlib::basic_vector::basic_vector(const entities::vertex& v0, const entities::vertex& v1):
	v0_(v0), v1_(v1), x_(v1_.x - v0_.x), y_(v1_.y - v0_.y), z_(v1.z - v0.z), has_verticies_(true)
{
	
}

dxflib::mathlib::basic_vector::basic_vector(const double x, const double y, const double z):
	v0_(0), v1_(0), x_(x), y_(y), z_(z), has_verticies_(false)
{

}

dxflib::mathlib::basic_vector::basic_vector(const dxflib::entities::geoline& gl) :
	v0_(gl[0]), v1_(gl[1]), x_(v1_.x - v0_.x), y_(v1_.y - v0_.y),
	z_(v1_.z - v0_.z), has_verticies_(true)
{

}

dxflib::entities::vertex& dxflib::mathlib::basic_vector::operator[](const int id)
{
	if (!has_verticies_)
		throw exceptions::no_associated_vertex("No Associated Vertex with Vector");

	switch (id)
	{
	case 0: return v0_;
	case 1: return v1_;
	default: throw std::invalid_argument("Invalid vertex ID");
	}
}

double dxflib::mathlib::basic_vector::magnitude() const
{
	if (has_verticies_)
		return distance(v0_, v1_);
	return sqrt(pow(x_, 2.0) + pow(y_, 2.0) + pow(z_, 2.0));
}

const dxflib::entities::vertex& dxflib::mathlib::basic_vector::operator[](const int id) const
{
	if (!has_verticies_)
		throw exceptions::no_associated_vertex("No Associated Vertex with Vector");

	switch (id)
	{
	case 0: return v0_;
	case 1: return v1_;
	default: throw std::invalid_argument("Invalid vertex ID");
	}
}

inline dxflib::mathlib::basic_vector dxflib::mathlib::basic_vector::operator+(const basic_vector& v) const
{
	return basic_vector{
		entities::vertex{v.v0_.x + v0_.x, v.v0_.y + v0_.y, v.v0_.z + v0_.z},
		entities::vertex{ v.v1_.x + v1_.x, v.v1_.y + v1_.y, v.v1_.z + v1_.z } };
}

inline dxflib::mathlib::basic_vector dxflib::mathlib::basic_vector::operator-(const basic_vector& v) const
{
	return basic_vector{
		entities::vertex{ v.v0_.x - v0_.x, v.v0_.y - v0_.y, v.v0_.z - v0_.z },
		entities::vertex{ v.v1_.x - v1_.x, v.v1_.y - v1_.y, v.v1_.z - v1_.z } };
}

double dxflib::mathlib::basic_vector::dot_product(const basic_vector& v0, const basic_vector& v1)
{
	return v1.x()*v0.x() + v1.y()*v0.y() + v1.z()*v0.z();
}

dxflib::mathlib::basic_vector dxflib::mathlib::basic_vector::cross_product(const basic_vector& v0,
	const basic_vector& v1)
{
	return basic_vector{ v0.y()*v1.z() - v1.y()*v0.z(),
						-(v0.x()*v1.z() - v1.x()*v0.z()),
						v0.x()*v1.y() - v1.x()*v0.y() };
}

int dxflib::mathlib::winding_num(const std::vector<entities::geoline>& geolines, const entities::vertex& v)
{
	/*
	 * This function uses the winding method to return the winding number of a polygon. 
	 * The winding number of a polygon is used to determing if a point is within a polygon.
	 * If the winding number is != 0 then the point is within the polygon. 
	 * 
	 * Method:
	 *		The function will iterate through all of the lines in a polygon (polyline) which in this library
	 *		are geolines. Each iteration will consist of the following method to determine the winding number:
	 *		
	 *		Firstly, a line vector is created: The line_vector is a vector that extends from the starting
	 *		point of the geoline to the ending point.
	 *		
	 *		Secondly, a point vector is created: The point vector extends from the point in question to the
	 *		starting point of the geoline.
	 *		
	 *		Then the cross product of the line vector and the point vector is taken (line_vector X point_vector)
	 *		If the cross product is less than 0 (product1 < 0) then this means that the point is to the right
	 *		of the current geoline segment and does not contribute to the winding number. If the cross product
	 *		is equal to 0 (product1 == 0) this means that the point is either: 1. On the line, 2. the line_vector
	 *		is a horizontal line or. If the cross product is > 0 then this means that the point in question is
	 *		to the left of the geoline and we must proceed to calculating the winding number for this segment.
	 *		
	 *		A position x vection is created: this vector is essentially a x unit vector that has a magnitude
	 *		of 1 in the x direction. The magnitude does not really matter it is more the direction that matters.
	 *		
	 *		Another cross product is taken (winding_cross) winding cross will determine if the current geoline 
	 *		segment is an "upward edge" or a "downward edge". if the cross product determines that this is an 
	 *		upward edge or has a value greater than 0: the winding number is increased, if the cross product
	 *		determines that the edge is a downward edge winding_cross <= 0 then sum is decremented by 1.
	 */
	int sum{ 0 };
	for (const auto& line : geolines)
	{
		const basic_vector line_vector{ line };
		if (line[0].y > v.y && line[1].y > v.y) // Line is above
			continue;
		if (line[0].y < v.y && line[1].y < v.y) // Line is below
			continue;
		if (line[0].x < v.x && line[1].x < v.x) // Line is to the right
			continue;

		const basic_vector x_position_vector{ 1, 0, 0 };
		const double winding_cross{ basic_vector::cross_product(x_position_vector, line_vector).z() };
		if (winding_cross <= 0)
			sum -= 1;
		else
			sum += 1;
	}
	return sum;
}

std::ostream& dxflib::mathlib::operator<<(std::ostream & os, const basic_vector & bv)
{
	os << "[" << bv.x() << "i, " << bv.y() << "j, " << bv.z() << "k]";
	return os;
}

