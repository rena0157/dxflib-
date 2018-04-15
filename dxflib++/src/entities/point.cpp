#include "dxflib++/include/entities/point.h"
#include <ostream>

dxflib::entities::point_base::point_base(const double x, const double y, const double z): x(x), y(y), z(z)
{
}

dxflib::entities::vertex::vertex(const double x, const double y, const double z) : point_base(x, y, z)
{

}

std::ostream& dxflib::entities::operator<<(std::ostream& os, point_base pb)
{
	os << "[" << pb.x << ", " << pb.y << ", " << pb.z << "]";
	return os;
}
