#pragma once

#include <cmath>
#include "matrix.h"

namespace xm
{
	template <typename T>
	matrix<T, 4> eulRotZ(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);

		vector<T, 4> a(cos_theta, sin_theta, 0.0, 0.0);
		vector<T, 4> b(-sin_theta, cos_theta, 0.0, 0.0);
		vector<T, 4> c(0.0, 0.0, 1.0, 0.0);
		vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

		matrix<T, 4> res(a, b, c, d);
		return res;
	}

	template <typename T>
	matrix<T, 4> eulRotX(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);

		vector<T, 4> a(1.0, 0.0, 0.0, 0.0);
		vector<T, 4> b(0.0, cos_theta, sin_theta, 0.0);
		vector<T, 4> c(0.0, -sin_theta, cos_theta, 0.0);
		vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

		matrix<T, 4> res(a, b, c, d);
		return res;
	}

	template <typename T>
	matrix<T, 4> eulRotY(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);

		vector<T, 4> a(cos_theta, 0.0, -sin_theta, 0.0);
		vector<T, 4> b(0.0, 1.0, 0.0, 0.0);
		vector<T, 4> c(sin_theta, 0.0, cos_theta, 0.0);
		vector<T, 4> d(0.0, 0.0, 0.0, 1.0);

		matrix<T, 4> res(a, b, c, d);
		return res;
	}
}