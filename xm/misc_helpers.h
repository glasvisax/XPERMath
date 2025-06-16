#pragma once

#include "vector.h"
#include "matrix.h"
#include "quaternion.h"

namespace xm
{
	template <uint8_t N, typename T>
	inline T* value_ptr(vector<N, T>& a)
	{
		return &(a.x);
	}

	template <uint8_t N, typename T>
	inline T* value_ptr(matrix<N, T>& a)
	{
		return &(a[0].x);
	}
}