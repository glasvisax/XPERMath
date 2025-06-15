#pragma once

#include <cstring>
#include "vector.h"

namespace xm
{
	template <uint8_t N, typename T>
	struct matrix;

	template <typename T>
	struct matrix<2, T>
	{
		static_assert(std::is_floating_point_v<T>);

		matrix()
		{
			this->a.x = 0.0;
			this->a.y = 0.0;
			this->b.x = 0.0;
			this->b.y = 0.0;
		}

		matrix(T a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->b.x = 0.0;
			this->b.y = a;
		}

		matrix(vector<2, T> a)
		{
			this->a = vector<T, 2>(a.x, 0.0);
			this->b = vector<T, 2>(0.0, a.y);
		}

		matrix(vector<2, T> a, vector<2, T> b)
		{
			this->a = a;
			this->b = b;
		}

		vector<2, T>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<2, T>& operator[] (uint8_t i) const
		{
			return (&a + i);
		}

		vector<2, T> a;
		vector<2, T> b;
	};

	template <typename T>
	struct matrix<3, T>
	{
		static_assert(std::is_floating_point_v<T>);

		matrix()
		{
			this->a.x = 0.0;
			this->a.y = 0.0;
			this->a.z = 0.0;

			this->b.x = 0.0;
			this->b.y = 0.0;
			this->b.z = 0.0;

			this->c.x = 0.0;
			this->c.y = 0.0;
			this->c.z = 0.0;
		}

		matrix(T a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->a.z = 0.0;

			this->b.x = 0.0;
			this->b.y = a;
			this->b.z = 0.0;

			this->c.x = 0.0;
			this->c.y = 0.0;
			this->c.z = a;
		}

		matrix(vector<3, T> a)
		{
			this->a = vector<T, 3>(a.x, 0.0, 0.0);
			this->b = vector<T, 3>(0.0, a.y, 0.0);
			this->c = vector<T, 3>(0.0, 0.0, a.z);
		}

		matrix(vector<3, T> a, vector<3, T> b, vector<3, T> c)
		{
			this->a = a;
			this->b = b;
			this->c = c;
		}

		vector<3, T>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<3, T>& operator[] (uint8_t i) const
		{
			return (&a + i);
		}

		vector<3, T> a;
		vector<3, T> b;
		vector<3, T> c;
	};

	template <typename T>
	struct matrix<4, T>
	{
		static_assert(std::is_floating_point_v<T>);

		matrix()
		{
			memset(&this->a.x, static_cast<int>(T(0.0)), 16 * sizeof(T));
		}

		matrix(T a)
		{
			this->a.x = a;
			this->a.y = 0.0;
			this->a.z = 0.0;
			this->a.w = 0.0;

			this->b.x = 0.0;
			this->b.y = a;
			this->b.z = 0.0;
			this->b.w = 0.0;

			this->c.x = 0.0;
			this->c.y = 0.0;
			this->c.z = a;
			this->c.w = 0.0;

			this->d.x = 0.0;
			this->d.y = 0.0;
			this->d.z = 0.0;
			this->d.w = a;
		}

		matrix(vector<3, T> a)
		{
			this->a = vector<T, 4>(a.x, 0.0, 0.0, 0.0);
			this->b = vector<T, 4>(0.0, a.y, 0.0, 0.0);
			this->c = vector<T, 4>(0.0, 0.0, a.z, 0.0);
			this->d = vector<T, 4>(0.0, 0.0, 0.0, 1.0);
		}
		matrix(vector<4, T> a)
		{
			this->a = vector<T, 4>(a.x, 0.0, 0.0, 0.0);
			this->b = vector<T, 4>(0.0, a.y, 0.0, 0.0);
			this->c = vector<T, 4>(0.0, 0.0, a.z, 0.0);
			this->d = vector<T, 4>(0.0, 0.0, 0.0, a.w);
		}

		matrix(const vector<4, T>& a, const vector<4, T>& b, const vector<4, T>& c, const vector<4, T>& d)
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		vector<4, T> a;
		vector<4, T> b;
		vector<4, T> c;
		vector<4, T> d;

		vector<4, T>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<4, T>& operator[] (uint8_t i) const
		{
			return *(&a + i);
		}
	};

	template <uint8_t N, typename T>
	matrix<N, T> operator*(matrix<N, T> a, matrix<N, T> b)
	{
		matrix<N, T> res;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				for (int k = 0; k < N; ++k)
				{
					res[i][j] += a[k][j] * b[i][k];
				}

			}
		}
		return res;
	}

	template <uint8_t N, typename T>
	vector<N, T> operator*(matrix<N, T> a, vector<N, T> b)
	{
		vector<N, T> res;
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				res[i] += a[j][i] * b[j];
			}
		}
		return res;
	}

}