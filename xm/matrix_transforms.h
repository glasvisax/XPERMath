#pragma once

#include <cmath>
#include "matrix.h"
#include <tuple>


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

			matrix<4, T> res(a, b, c, d);
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

	// axis		- asix of rotation, must be unit vector
	// rotated	- rotated vector
	// radians	- angle in radians
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
	matrix<N, T> scale(const matrix<N, T>& scaled, vector<3, T> scale_vec)
	{
		if constexpr (N == 3)
		{
			vector<3, T> a = scaled.a * scale_vec.x;
			vector<3, T> b = scaled.b * scale_vec.y;
			vector<3, T> c = scaled.c * scale_vec.z;
			return matrix<3, T>(a, b, c);
		}
		else if constexpr (N == 4)
		{
			vector<4, T> a = vector<4, T>(scaled.a.x * scale_vec.x,
				scaled.a.y * scale_vec.x,
				scaled.a.z * scale_vec.x,
				scaled.a.w);
			vector<4, T> b = vector<4, T>(scaled.b.x * scale_vec.y,
				scaled.b.y * scale_vec.y,
				scaled.b.z * scale_vec.y,
				scaled.b.w);
			vector<4, T> c = vector<4, T>(scaled.c.x * scale_vec.z,
				scaled.c.y * scale_vec.z,
				scaled.c.z * scale_vec.z,
				scaled.c.w);
			vector<4, T> d = scaled.d;
			return matrix<4, T>(a, b, c, d);
		}
		else
		{
			static_assert(false, "N must be 3 or 4");
		}
	}

	template <typename T>
	matrix<4, T> translate(const matrix<4, T>& translated, vector<3, T> translation)
	{
		vector<4, T> last_column(translated.d.x + translation.x, translated.d.y + translation.y, translated.d.z + translation.z, 1.0);
		return matrix<4, T>(translated.a, translated.b, translated.c, last_column);
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit 
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T>
	std::tuple<matrix<4, T>, vector<3, T>, vector<3, T>> lookAtRH(vector<3, T> eye_pos, vector<3, T> look_dir, vector<3, T> world_up)
	{
		vector<3, T> x = crossRH(world_up, -look_dir);
		vector<3, T> y = crossRH(-look_dir, x);
		vector<3, T> z = -look_dir;

		vector<4, T> a(x.x, y.x, z.x, 0.0);
		vector<4, T> b(x.y, y.y, z.y, 0.0);
		vector<4, T> c(x.z, y.z, z.z, 0.0);
		vector<4, T> d(dot(x, -eye_pos), dot(y, -eye_pos), dot(z, -eye_pos), 1.0);

		return std::make_tuple(matrix<4, T>(a, b, c, d), x, y);
	}

	// eye_pos		-	view position
	// look_dir		-	direction of view, must be unit 
	// eye_up		-	view up direcion, must be unit
	// eye_right	-	view right direcion, must be unit
	// return		-	tuple [view matrix, right vector, up vector]
	template <typename T>
	matrix<4, T> lookAtRH_EXT(vector<3, T> eye_pos, vector<3, T> look_dir, vector<3, T> eye_up, vector<3, T> eye_right)
	{
		vector<3, T> x = eye_right;
		vector<3, T> y = eye_up;
		vector<3, T> z = -look_dir;

		vector<4, T> a(x.x, y.x, z.x, 0.0);
		vector<4, T> b(x.y, y.y, z.y, 0.0);
		vector<4, T> c(x.z, y.z, z.z, 0.0);
		vector<4, T> d(dot(x, -eye_pos), dot(y, -eye_pos), dot(z, -eye_pos), 1.0);

		return matrix<4, T>(a, b, c, d);
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit 
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T>
	std::tuple<matrix<4, T>, vector<3, T>, vector<3, T>> lookAtLH(vector<3, T> eye_pos, vector<3, T> look_dir, vector<3, T> world_up)
	{
		vector<3, T> x = crossLH(world_up, -look_dir);
		vector<3, T> y = crossLH(-look_dir, x);
		vector<3, T> z = look_dir;

		vector<4, T> a(x.x, y.x, z.x, 0.0);
		vector<4, T> b(x.y, y.y, z.y, 0.0);
		vector<4, T> c(x.z, y.z, z.z, 0.0);
		vector<4, T> d(dot(x, -eye_pos), dot(y, -eye_pos), dot(z, -eye_pos), 1.0);

		return std::make_tuple(matrix<4, T>(a, b, c, d), x, y);
	}

	// eye_pos		-	view position
	// look_dir		-	direction of view, must be unit 
	// eye_up		-	view up direcion, must be unit
	// eye_right	-	view right direcion, must be unit
	// return		-	tuple [view matrix, right vector, up vector]
	template <typename T>
	matrix<4, T> lookAtLH_EXT(vector<3, T> eye_pos, vector<3, T> look_dir, vector<3, T> eye_up, vector<3, T> eye_right)
	{
		lookAtRH_EXT(eye_pos, -look_dir, eye_up, eye_right);
	}

	// eye_pos	-	view position
	// look_dir	-	direction of view, must be unit 
	// world_up -	world up vector, must be unit
	// return	-	tuple [view matrix, right vector, up vector]
	template <typename T>
	inline std::tuple<matrix<4, T>, vector<3, T>, vector<3, T>> lookAt(vector<3, T> eye_pos, vector<3, T> center, vector<3, T> world_up = vector<3, T>(0.0, 1.0, 0.0))
	{
		vector<3, T> look_dir = center - eye_pos;
		return lookAtRH(eye_pos, look_dir, world_up);
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