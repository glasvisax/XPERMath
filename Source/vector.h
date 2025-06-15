#pragma once

#include <type_traits>
#include "assert.h"

namespace xm
{
	template <uint8_t N, typename T>
	struct vector;

	template<typename T>
	struct vector<2, T>
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
	struct vector<3, T>
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
	struct vector<4, T>
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

	template <uint8_t N, typename T>
	T dot(vector<N, T> a, vector<N, T> b)
	{
		T res = T(0.0);

		for (int i = 0; i < N; ++i)
		{
			res += a[i] * b[i];
		}

		return res;
	}

	template <typename T>
	vector<3, T> crossRH(vector<3, T> a, vector<3, T> b)
	{
		vector<T, 3> res;

		res.x = a.y * b.z - a.z * b.y;
		res.y = a.z * b.x - a.x * b.z;
		res.z = a.x * b.y - a.y * b.x;

		return res;
	}

	template <typename T>
	inline vector<3, T> crossLH(vector<3, T> a, vector<3, T> b)
	{
		return -crossRH(a, b);
	}

	template <typename T>
	inline vector<3, T> cross(vector<3, T> a, vector<3, T> b)
	{
		return crossRH(a, b);
	}

	template <typename T>
	T cross2D(vector<2, T> a, vector<2, T> b)
	{
		return a.x * b.y - a.y * b.x;
	}

	template <uint8_t N, typename T>
	vector<N, T> operator*(vector<N, T> a, T v)
	{
		vector<T, N> res;
		for (int i = 0; i < N; ++i)
		{
			res[i] = a[i] * v;
		}
		return res;
	}

	template <uint8_t N, typename T>
	inline vector<N, T> operator*(T v, vector<N, T> a)
	{
		return operator*(a, v);
	}

	template <uint8_t N, typename T>
	vector<N, T> operator+(vector<N, T> a, vector<N, T> b)
	{
		vector<T, N> res;
		for (int i = 0; i < N; ++i)
		{
			res[i] = a[i] + b[i];
		}
		return res;
	}

	template <uint8_t N, typename T>
	inline vector<N, T> operator-(vector<N, T> a, vector<N, T> b)
	{
		return operator+(a, -b);
	}

	template < uint8_t N, typename T>
	inline T sumOfSquares(vector<N, T> a)
	{
		T sum = 0.0;
		for (int i = 0; i < N; ++i)
		{
			sum += a[i] * a[i];
		}
		return sum;
	}

	template < uint8_t N, typename T>
	inline T normalize(vector<N, T> a)
	{
		return sqrt(sumOfSquares(a));
	}

}



