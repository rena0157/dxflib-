#include "dxflib++/include/entities/point.h"
#include "dxflib++/include/entities/lwpolyline.h"
#include "dxflib++/include/mathlib.h"
#include <ostream>

dxflib::entities::point_base::point_base(const double x, const double y, const double z):
	x(x), y(y), z(z)
{
}

dxflib::entities::vertex::vertex(const double x, const double y, const double z) :
	point_base(x, y, z)
{
}

bool dxflib::entities::vertex::within(const lwpolyline& pl) const
{
	if (!pl.is_closed())
		return false;
	return mathlib::winding_num(pl.get_lines(), *this);
}

std::ostream& dxflib::entities::operator<<(std::ostream& os, const point_base pb)
{
	os << "[" << pb.x << ", " << pb.y << ", " << pb.z << "]";
	return os;
}
