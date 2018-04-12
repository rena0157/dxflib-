#pragma once
#include "entities/point.h"
#include <cmath>

namespace dxflib
{
	namespace mathlib
	{
		inline double distance(const entities::vertex& v0, const entities::vertex& v1)
		{
			return sqrt(pow(v1.x - v0.x, 2) + pow(v1.y - v0.y, 2) + pow(v1.z - v0.z, 2));
		}
		inline double distance(const entities::vertex& v0, const entities::vertex& v1, const double bulge)
		{
			return distance(v0, v1)/(2*sin(4*atan(bulge)/2))*4*atan(bulge);
		}

	}
}
