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
		return matrix<4, T>(translated.a, translated.b, translated.c, last_column);
	}

	template <typename T>
	matrix<4, T> lookAtRH(vector<3, T> look_dir, vector<3, T> eye_pos, vector<3, T> world_up)
	{
		vector<3, T> x = normalize(crossRH(world_up, -look_dir));
		vector<3, T> y = normalize(crossRH(-look_dir, x));
		vector<3, T> z = normalize(-look_dir);

		vector<4, T> a(x.x, y.x, z.x, 0.0);
		vector<4, T> b(x.y, y.y, z.y, 0.0);
		vector<4, T> c(x.z, y.z, z.z, 0.0);
		vector<4, T> d(dot(x, -eye_pos), dot(y, -eye_pos), dot(z, -eye_pos), 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> lookAtLH(vector<3, T> look_dir, vector<3, T> eye_pos, vector<3, T> world_up)
	{
		vector<3, T> x = normalize(crossLH(world_up, -look_dir));
		vector<3, T> y = normalize(crossLH(-look_dir, x));
		vector<3, T> z = normalize(look_dir);

		vector<4, T> a(x.x, y.x, z.x, 0.0);
		vector<4, T> b(x.y, y.y, z.y, 0.0);
		vector<4, T> c(x.z, y.z, z.z, 0.0);
		vector<4, T> d(dot(x, -eye_pos), dot(y, -eye_pos), dot(z, -eye_pos), 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> lookAt(vector<3, T> look_dir, vector<3, T> eye_pos, vector<3, T> world_up = vector<3, T>(0.0, 1.0, 0.0))
	{
		return lookAtRH(look_dir, eye_pos, world_up);
	}

	template <typename T>
	matrix<4, T> perspectiveLH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		T _2n = 2 * near;
		T r_minus_l = right - left;
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;

		vector<4, T> a(_2n / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, _2n / t_minus_b, 0.0, 0.0);
		vector<4, T> c(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			-(far + near) / n_minus_f,
			1.0);
		vector<4, T> d(0.0, 0.0, (_2n * far) / n_minus_f, 0.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> perspectiveRH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		T _2n = 2 * near;
		T r_minus_l = right - left;
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;

		vector<4, T> a(_2n / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, _2n / t_minus_b, 0.0, 0.0);
		vector<4, T> c(
			(right + left) / r_minus_l,
			(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			-1.0);
		vector<4, T> d(0.0, 0.0, (_2n * far) / n_minus_f, 0.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> perspectiveLH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;
		vector<4, T> a(near / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, near / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, -(far + near) / n_minus_f, 1.0);
		vector<4, T> d(0.0, 0.0, (2 * near * far) / n_minus_f, 0.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> perspectiveRH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;
		vector<4, T> a(near / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, near / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, (far + near) / n_minus_f, -1.0);
		vector<4, T> d(0.0, 0.0, (2 * near * far) / n_minus_f, 0.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> perspectiveLH_FOV(T fov_vert_radians, T aspect, T near, T far)
	{
		T top = tan(fov_vert_radians / 2) * near;
		T right = top * aspect;

		return perspectiveLH_STRIP(top, right, near, far);
	}

	template <typename T>
	inline matrix<4, T> perspectiveRH_FOV(T fov_vert_radians, T aspect, T near, T far)
	{
		T top = tan(fov_vert_radians / 2) * near;
		T right = top * aspect;

		return perspectiveRH_STRIP(top, right, near, far);
	}

	template <typename T>
	inline matrix<4, T> perspective(T fov_vert_radians, T aspect, T near, T far)
	{
		return perspectiveRH_FOV(fov_vert_radians, aspect, near, far);
	}

	template <typename T>
	matrix<4, T> orthographicLH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(2.0 / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 2.0 / t_minus_b, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, -2.0 / n_minus_f, 0.0);
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	matrix<4, T> orthographicLH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;

		vector<4, T> a(1.0 / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 1.0 / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, -2.0 / n_minus_f, 0.0);
		vector<4, T> d(0.0, 0.0, (far + near) / n_minus_f, 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_EXT(T top, T bottom, T right, T left, T near, T far)
	{
		T t_minus_b = top - bottom;
		T n_minus_f = near - far;
		T r_minus_l = right - left;

		vector<4, T> a(2.0 / r_minus_l, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 2.0 / t_minus_b, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, 2.0 / n_minus_f, 0.0);
		vector<4, T> d(
			-(right + left) / r_minus_l,
			-(top + bottom) / t_minus_b,
			(far + near) / n_minus_f,
			1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographicRH_STRIP(T top, T right, T near, T far)
	{
		T n_minus_f = near - far;

		vector<4, T> a(1.0 / right, 0.0, 0.0, 0.0);
		vector<4, T> b(0.0, 1.0 / top, 0.0, 0.0);
		vector<4, T> c(0.0, 0.0, 2.0 / n_minus_f, 0.0);
		vector<4, T> d(0.0, 0.0, (far + near) / n_minus_f, 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	template <typename T>
	inline matrix<4, T> orthographic(T top, T bottom, T right, T left, T near, T far)
	{
		return orthographicRH_EXT(top, bottom, right, left, near, far);
	}
}