#include "dxflib++/include/entities/point.h"

dxflib::entities::point_base::point_base(const double x, const double y, const double z): x(x), y(y), z(z)
{
}

dxflib::entities::vertex::vertex(const double x, const double y, const double z) : point_base(x, y, z)
{

}
