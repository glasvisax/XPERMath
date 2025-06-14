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

	/// <summary>
	/// returns rodrigues rotation matrix
	/// </summary>
	/// <typeparam name="T">float point type</typeparam>
	/// <typeparam name="N">3 or 4 dimension of matrix</typeparam>
	/// <param name="axis">axis of rotation of unit length</param>
	/// <param name="radians">rotation angle in radians</param>
	/// <returns>rodrigues rotation matrix</returns>
	template <uint8_t N, typename T>
	matrix<T, N> rodriguesMatrix(vector<T, 3> axis, T radians)
	{
		T s = sin(radians);
		T c = cos(radians);
		T ic = 1 - c;
		if constexpr (N == 3)
		{
			vector<T, 3> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s
			);

			vector<T, 3> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s
			);

			vector<T, 3> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic
			);

			matrix<T, 3> res(a1, a2, a3);
			return res;
		}
		else if constexpr (N == 4)
		{
			vector<T, 4> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s,
				0.0
			);

			vector<T, 4> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s,
				0.0
			);

			vector<T, 4> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic,
				0.0
			);
			vector<T, 4> a4(
				0.0,
				0.0,
				0.0,
				1.0
			);

			matrix<T, 4> res(a1, a2, a3, a4);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}

	}
}