#pragma once

#include <cmath>
#include "matrix.h"

namespace xm
{
	template <uint8_t N, typename T>
	matrix<N, T> eulRotZ(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, T> a(cos_theta, sin_theta, 0.0, 0.0);
			vector<4, T> b(-sin_theta, cos_theta, 0.0, 0.0);
			vector<4, T> c(0.0, 0.0, 1.0, 0.0);
			vector<4, T> d(0.0, 0.0, 0.0, 1.0);

			matrix<4, T> res(a, b, c, d);
			return res;
		}
		else if constexpr (N == 3)
		{
			vector<3, T> a(cos_theta, sin_theta, 0.0);
			vector<3, T> b(-sin_theta, cos_theta, 0.0);
			vector<3, T> c(0.0, 0.0, 1.0);

			matrix<3, T> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	template <uint8_t N, typename T>
	matrix<N, T> eulRotX(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, T> a(1.0, 0.0, 0.0, 0.0);
			vector<4, T> b(0.0, cos_theta, sin_theta, 0.0);
			vector<4, T> c(0.0, -sin_theta, cos_theta, 0.0);
			vector<4, T> d(0.0, 0.0, 0.0, 1.0);

			matrix<4, T> res(a, b, c, d);
			return res;
		}
		else if constexpr (N == 3)
		{
			vector<3, T> a(1.0, 0.0, 0.0);
			vector<3, T> b(0.0, cos_theta, sin_theta);
			vector<3, T> c(0.0, -sin_theta, cos_theta);

			matrix<3, T> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	template <uint8_t N, typename T>
	matrix<N, T> eulRotY(T radians)
	{
		T cos_theta = cos(radians);
		T sin_theta = sin(radians);
		if constexpr (N == 4)
		{
			vector<4, T> a(cos_theta, 0.0, -sin_theta, 0.0);
			vector<4, T> b(0.0, 1.0, 0.0, 0.0);
			vector<4, T> c(sin_theta, 0.0, cos_theta, 0.0);
			vector<4, T> d(0.0, 0.0, 0.0, 1.0);

			matrix<T, 4> res(a, b, c, d);
			return res;

		}
		else if constexpr (N == 3)
		{
			vector<3, T> a(cos_theta, 0.0, -sin_theta);
			vector<3, T> b(0.0, 1.0, 0.0);
			vector<3, T> c(sin_theta, 0.0, cos_theta);

			matrix<3, T> res(a, b, c);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	// axis must be unit vector
	template <uint8_t N, typename T>
	matrix<N, T> rodriguesMatrix(vector<3, T> axis, T radians)
	{
		T s = sin(radians);
		T c = cos(radians);
		T ic = 1 - c;
		if constexpr (N == 3)
		{
			vector<3, T> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s
			);

			vector<3, T> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s
			);

			vector<3, T> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic
			);

			matrix<3, T> res(a1, a2, a3);
			return res;
		}
		else if constexpr (N == 4)
		{
			vector<4, T> a1(
				c + axis.x * axis.x * ic,
				axis.x * axis.y * ic + axis.z * s,
				axis.x * axis.z * ic - axis.y * s,
				0.0
			);

			vector<4, T> a2(
				axis.x * axis.y * ic - axis.z * s,
				c + axis.y * axis.y * ic,
				axis.y * axis.z * ic + axis.x * s,
				0.0
			);

			vector<4, T> a3(
				axis.x * axis.z * ic + axis.y * s,
				axis.y * axis.z * ic - axis.x * s,
				c + axis.z * axis.z * ic,
				0.0
			);
			vector<4, T> a4(
				0.0,
				0.0,
				0.0,
				1.0
			);

			matrix<4, T> res(a1, a2, a3, a4);
			return res;
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}

	}

	// axis must be unit vector
	template <uint8_t N, typename T>
	matrix<N, T> rotate(const matrix<N, T>& rotated, vector<3, T> axis, T radians)
	{
		if constexpr (N != 3 && N != 4)
		{
			static_assert(false && "N must be 3 or 4");
		}
		matrix<N, T> rotation_matrix = rodriguesMatrix<N>(axis, radians);
		return rotated * rotation_matrix;
	}

	template <uint8_t N, typename T>
	matrix<N, T> scale(const matrix<N, T>& scaled, vector<3, T> scale)
	{
		if constexpr (N == 3)
		{
			vector<3, T> a(scaled.a.x * scale.x, scaled.a.y * scale.y, scaled.a.z * scale.z);
			vector<3, T> b(scaled.b.x * scale.x, scaled.b.y * scale.y, scaled.b.z * scale.z);
			vector<3, T> c(scaled.c.x * scale.x, scaled.c.y * scale.y, scaled.c.z * scale.z);
			return matrix<3, T>(a, b, c, d);
		}
		else if constexpr (N == 4)
		{
			vector<4, T> a(scaled.a.x * scale.x, scaled.a.y * scale.y, scaled.a.z * scale.z, 0.0);
			vector<4, T> b(scaled.b.x * scale.x, scaled.b.y * scale.y, scaled.b.z * scale.z, 0.0);
			vector<4, T> c(scaled.c.x * scale.x, scaled.c.y * scale.y, scaled.c.z * scale.z, 0.0);
			vector<4, T> d(scaled.d.x * scale.x, scaled.d.y * scale.y, scaled.d.z * scale.z, 1.0);
			return matrix<4, T>(a, b, c, d);
		}
		else
		{
			static_assert(false && "N must be 3 or 4");
		}
	}

	template <typename T>
	matrix<4, T> translate(const matrix<4, T>& translated, vector<3, T> translation)
	{
		vector<4, T> last_column(translated.d.x + translation.x, translated.d.y + translation.y, translated.d.z + translation.z, 1.0);
		matrix<4, T> translation_matrix(translated.a, translated.b, translated.c, last_column);

		return translation_matrix;
	}

}