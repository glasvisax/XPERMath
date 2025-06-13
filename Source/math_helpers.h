#pragma once

#include "constants.h"

namespace xm
{
	template <typename T>
	T to_radians(T degrees)
	{
		return PI_OV_180 * degrees;
	}

	template <typename T>
	T to_degrees(T radians)
	{
		return 180.0 / PI * radians;
	}
}