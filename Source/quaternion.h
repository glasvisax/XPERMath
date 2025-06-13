#pragma once

#include <cmath>
#include "vector.h"
#include "matrix.h"

namespace xm
{
	template <typename T>
	struct quaternion
	{
		quaternion() = default;
		quaternion(T w, vector<T, 3> m) : w(w), m(m) {}

		T w;
		vector<T, 3> m;
	};

	template <typename T>
	quaternion<T> operator*(quaternion<T> a, quaternion<T> b)
	{
		quaternion<T> res;

		res.w = a.w * b.w - dot(a.m, b.m);
		res.m = a.w * b.m + b.w * a.m + cross(a.m, b.m);

		return res;
	}

	template <typename T>
	quaternion<T> operator*(quaternion<T> a, T v)
	{
		quaternion<T> res;

		res.w = a.w * v;
		res.m = a.m * v;

		return res;
	}

	template <typename T>
	inline quaternion<T> operator*(T v, quaternion<T> a)
	{
		return operator*(a, v);
	}

	template <typename T>
	quaternion<T> operator+(quaternion<T> a, quaternion<T> b)
	{
		return quaternion<T>(a.w + b.w, a.m + b.m);
	}

	template <typename T>
	quaternion<T> operator-(quaternion<T> a, quaternion<T> b)
	{
		return quaternion<T>(a.w - b.w, a.m - b.m);
	}

	template <typename T>
	quaternion<T> operator/(quaternion<T> a, T v)
	{
		quaternion<T> res;

		res.w = a.w * v;
		res.m = a.m * v;

		return res;
	}

	template <typename T>
	inline quaternion<T> operator/(T v, quaternion<T> a)
	{
		return operator/(a, v);
	}

	template <typename T>
	T dot(quaternion<T> a, quaternion<T> b)
	{
		T res = a.w * b.w;
		res += dot(a.m, b.m);
		return res;
	}

	template <typename T>
	inline quaternion<T> conjugate(quaternion<T> q)
	{
		return quaternion<T>(q.w, -q.m);
	}

	template <typename T>
	T length(quaternion<T> q)
	{
		return sqrt(q.w * q.w + dot(q.m, q.m));
	}

	template <typename T>
	quaternion<T> normalize(quaternion<T> q)
	{
		return q / length(q);
	}

	template <typename T>
	matrix<T, 3> mat3_cast(quaternion<T> a)
	{
		T x_2 = a.m.x * a.m.x;
		T y_2 = a.m.y * a.m.y;
		T z_2 = a.m.z * a.m.z;

		T xy = a.m.x * a.m.y;
		T xz = a.m.x * a.m.z;
		T yz = a.m.y * a.m.z;

		T wy = a.w * a.m.y;
		T wx = a.w * a.m.x;
		T wz = a.w * a.m.z;

		vector<T, 3> c1(
			1 - 2 * y_2 - 2 * z_2,
			2 * xy + 2 * wz,
			2 * xz - 2 * wy
		);

		vector<T, 3> c2(
			2 * xy - 2 * wz,
			1 - 2 * x_2 - 2 * z_2,
			2 * yz + 2 * wz
		);

		vector<T, 3> c3(
			2 * xz + 2 * wy,
			2 * yz - 2 * wx,
			1 - 2 * x_2 - 2 * y_2
		);

		matrix<T, 3> res(c1, c2, c3);

		return res;
	}


	template <typename T>
	matrix<T, 4> mat4_cast(quaternion<T> a)
	{
		T x_2 = a.m.x * a.m.x;
		T y_2 = a.m.y * a.m.y;
		T z_2 = a.m.z * a.m.z;

		T xy = a.m.x * a.m.y;
		T xz = a.m.x * a.m.z;
		T yz = a.m.y * a.m.z;

		T wy = a.w * a.m.y;
		T wx = a.w * a.m.x;
		T wz = a.w * a.m.z;

		vector<T, 4> c1(
			1 - 2 * y_2 - 2 * z_2,
			2 * xy + 2 * wz,
			2 * xz - 2 * wy,
			0.0f
		);

		vector<T, 4> c2(
			2 * xy - 2 * wz,
			1 - 2 * x_2 - 2 * z_2,
			2 * yz + 2 * wz,
			0.0f
		);

		vector<T, 4> c3(
			2 * xz + 2 * wy,
			2 * yz - 2 * wx,
			1 - 2 * x_2 - 2 * y_2,
			0.0f
		);

		vector<T, 4> c4(T(0.0), T(0.0), T(0.0), T(1.0));

		matrix<T, 4> res(c1, c2, c3, c4);

		return res;
	}

	template <typename T>
	quaternion<T> lerp(quaternion<T> a, quaternion<T> b, long double t)
	{
		return (1 - t) * a + t * b;
	}

	template <typename T>
	quaternion<T> slerp(quaternion<T> q1, quaternion<T> q2, long double t)
	{
		T cos_theta = dot(q1, q2);
		if (cos_theta < 0)
		{
			cos_theta = -cos_theta;
		}

		if (cos_theta > 0.995)
		{
			return normalize(lerp(q1, q2, t));
		}

		long double theta = acos(cos_theta);
		T sin_theta = sqrt(1 - cos_theta * cos_theta);

		long double a = sin((1 - t) * theta) / sin_theta;

		long double b = sin(t * theta) / sin_theta;

		quaternion<T> res = a * q1 + b * q2;

		return res;
	}

	template <typename T>
	quaternion<T> quat_from_euler_x(T x)
	{
		return quaternion<T>(
			cos(e.x / 2),
			vector<T, 3>(
				sin(e.x / 2),
				T(0.0),
				T(0.0)
			)
		);
	}

	template <typename T>
	quaternion<T> quat_from_euler_y(T y)
	{
		return quaternion<T>(
			cos(e.y / 2),
			vector<T, 3>(
				T(0.0),
				sin(e.y / 2),
				T(0.0)
			)
		);
	}
	template <typename T>
	quaternion<T> quat_from_euler_z(T z)
	{
		return quaternion<T>(
			cos(e.z / 2),
			vector<T, 3>(
				T(0.0),
				T(0.0),
				sin(e.z / 2)
			)
		);

	}

	template <typename T>
	quaternion<T> quat_from_euler_xyz(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qz * qy * qx);
	}

	template <typename T>
	quaternion<T> quat_from_euler_xzy(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qy * qz * qx);
	}

	template <typename T>
	quaternion<T> quat_from_euler_yxz(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qz * qx * qy);
	}

	template <typename T>
	quaternion<T> quat_from_euler_yzx(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qx * qz * qy);
	}

	template <typename T>
	quaternion<T> quat_from_euler_zxy(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qy * qx * qz);
	}

	template <typename T>
	quaternion<T> quat_from_euler_zyx(vector<T, 3> e)
	{
		quaternion<T> qx = quat_from_euler_x(e.x);
		quaternion<T> qy = quat_from_euler_y(e.y);
		quaternion<T> qz = quat_from_euler_z(e.z);

		return normalize(qx * qy * qz);
	}
}


