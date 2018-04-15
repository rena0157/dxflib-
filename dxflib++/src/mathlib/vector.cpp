#include "dxflib++/include/mathlib.h"

dxflib::mathlib::basic_vector::basic_vector():
	v0_(0,0,0), v1_(0,0,0)
{

}

dxflib::mathlib::basic_vector::basic_vector(entities::vertex& v0, entities::vertex& v1):
	v0_(v0), v1_(v1)
{
	
}

dxflib::entities::vertex& dxflib::mathlib::basic_vector::operator[](const int id)
{
	switch (id)
	{
	case 0: return v0_;
	case 1: return v1_;
	default: throw std::invalid_argument("Invalid vertex ID");
	}
}

const dxflib::entities::vertex& dxflib::mathlib::basic_vector::operator[](const int id) const
{
	switch (id)
	{
	case 0: return v0_;
	case 1: return v1_;
	default: throw std::invalid_argument("Invalid vertex ID");
	}
}


