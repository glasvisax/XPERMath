#pragma once

#include <type_traits>
#include "assert.h"

namespace xm
{
	template <typename T, uint8_t N>
	struct vector;

	template<typename T>
	struct vector<T, 2>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);

		vector(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		vector(T a)
		{
			this->x = a;
			this->y = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		void operator-()
		{
			x = -x;
			y = -y;
		}

		union
		{
			struct { T x, y; };
			struct { T r, g; };
			struct { T u, v; };
		};

	};

	template<typename T>
	struct vector<T, 3>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);
		vector(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vector(T a)
		{
			this->x = a;
			this->y = a;
			this->z = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		void operator-()
		{
			x = -x;
			y = -y;
			z = -z;
		}

		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};
	};


	template<typename T>
	struct vector<T, 4>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);
		vector(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vector(T a)
		{
			this->x = a;
			this->y = a;
			this->z = a;
			this->w = a;
		}

		vector()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

		void operator-()
		{
			x = -x;
			y = -y;
			z = -z;
			w = -w;
		}

		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
	};

	template <typename T, uint8_t N>
	T dot(vector<T, N> a, vector<T, N> b)
	{
		T res = T(0.0);

		for (int i = 0; i < N; ++i)
		{
			res += a[i] * b[i];
		}

		return res;
	}

	template <typename T>
	vector<T, 3> crossRH(vector<T, 3> a, vector<T, 3> b)
	{
		vector<T, 3> res;

		res.x = a.y * b.z - a.z * b.y;
		res.y = a.z * b.x - a.x * b.z;
		res.z = a.x * b.y - a.y * b.x;

		return res;
	}

	template <typename T>
	inline vector<T, 3> crossLH(vector<T, 3> a, vector<T, 3> b)
	{
		return -crossRH(a, b);
	}

	template <typename T>
	inline vector<T, 3> cross(vector<T, 3> a, vector<T, 3> b)
	{
		return crossRH(a, b);
	}

	template <typename T>
	T cross2D(vector<T, 2> a, vector<T, 2> b)
	{
		return a.x * b.y - a.y * b.x;
	}

	template <typename T, uint8_t N>
	vector<T, N> operator*(vector<T, N> a, T v)
	{
		vector<T, N> res;
		for (int i = 0; i < N; ++i)
		{
			res[i] = a[i] * v;
		}
		return res;
	}

	template <typename T, uint8_t N>
	inline vector<T, N> operator*(T v, vector<T, N> a)
	{
		return operator*(a, v);
	}

	template <typename T, uint8_t N>
	vector<T, N> operator+(vector<T, N> a, vector<T, N> b)
	{
		vector<T, N> res;
		for (int i = 0; i < N; ++i)
		{
			res[i] = a[i] + b[i];
		}
		return res;
	}

	template <typename T, uint8_t N>
	inline vector<T, N> operator-(vector<T, N> a, vector<T, N> b)
	{
		return operator+(a, -b);
	}

	template <typename T, uint8_t N>
	inline T sumOfSquares(vector<T, N> a)
	{
		T sum = 0.0;
		for (int i = 0; i < N; ++i)
		{
			sum += a[i] * a[i];
		}
		return sum;
	}

	template <typename T, uint8_t N>
	inline T normalize(vector<T, N> a)
	{
		return sqrt(sumOfSquares(a));
	}

}



