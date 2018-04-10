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
			// TODO: Implement this function
			return 0;
		}
	}
}
