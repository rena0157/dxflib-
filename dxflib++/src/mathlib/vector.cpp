#include "dxflib++/include/mathlib.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include <iostream>

dxflib::mathlib::basic_vector::basic_vector(const entities::vertex& v0, const entities::vertex& v1):
	v0_(v0), v1_(v1), x_(v1_.x - v0_.x), y_(v1_.y - v0_.y), z_(v1.z - v0.z), has_verticies_(true)
{
	
}

dxflib::mathlib::basic_vector::basic_vector(const double x, const double y, const double z):
	v0_(0), v1_(0), x_(x), y_(y), z_(z), has_verticies_(false)
{

}

dxflib::mathlib::basic_vector::basic_vector(dxflib::entities::geoline& gl) :
	v0_(gl[0]), v1_(gl[1]), x_(gl[1].x - gl[0].x), y_(gl[1].y - gl[0].y),
	z_(gl[1].z - gl[0].z), has_verticies_(true)
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

std::ostream& dxflib::mathlib::operator<<(std::ostream & os, const basic_vector & bv)
{
	os << "[" << bv.x() << "i, " << bv.y() << "j, " << bv.z() << "k]";
	return os;
}

