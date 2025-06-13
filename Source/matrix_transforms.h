#pragma once

#include <cmath>
#include "matrix.h"

namespace xm
{
	template <uint8_t N, typename T>
	matrix<T, N> eulRotZ(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<T, 4> a(cos_theta, sin_theta, 0.0, 0.0);
			vector<T, 4> b(-sin_theta, cos_theta, 0.0, 0.0);
			vector<T, 4> c(0.0, 0.0, 1.0, 0.0);
			vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

			matrix<T, 4> res(a, b, c, d);
			return res;
		}
		else if constexpr (N == 3)
		{
			vector<T, 3> a(cos_theta, sin_theta, 0.0);
			vector<T, 3> b(-sin_theta, cos_theta, 0.0);
			vector<T, 3> c(0.0, 0.0, 1.0);

			matrix<T, 3> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	template <uint8_t N, typename T>
	matrix<T, N> eulRotX(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<T, 4> a(1.0, 0.0, 0.0, 0.0);
			vector<T, 4> b(0.0, cos_theta, sin_theta, 0.0);
			vector<T, 4> c(0.0, -sin_theta, cos_theta, 0.0);
			vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

			matrix<T, 4> res(a, b, c, d);
			return res;
		}
		else if constexpr (N == 3)
		{
			vector<T, 3> a(1.0, 0.0, 0.0);
			vector<T, 3> b(0.0, cos_theta, sin_theta);
			vector<T, 3> c(0.0, -sin_theta, cos_theta);

			matrix<T, 3> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	template <uint8_t N, typename T>
	matrix<T, N> eulRotY(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<T, 4> a(cos_theta, 0.0, -sin_theta, 0.0);
			vector<T, 4> b(0.0, 1.0, 0.0, 0.0);
			vector<T, 4> c(sin_theta, 0.0, cos_theta, 0.0);
			vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

			matrix<T, 4> res(a, b, c, d);
			return res;

		}
		else if constexpr (N == 3)
		{
			vector<T, 3> a(cos_theta, 0.0, -sin_theta);
			vector<T, 3> b(0.0, 1.0, 0.0);
			vector<T, 3> c(sin_theta, 0.0, cos_theta);

			matrix<T, 3> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}
}