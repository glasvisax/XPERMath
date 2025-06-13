#pragma once

#include <cstring>
#include "vector.h"

namespace xm
{
	template <typename T, uint8_t N>
	struct matrix;

	template <typename T>
	struct matrix<T, 2>
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

		matrix(const vector<T, 2>& a, const vector<T, 2>& b)
		{
			this->a = a;
			this->b = b;
		}

		vector<T, 2>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<T, 2>& operator[] (uint8_t i) const
		{
			return (&a + i);
		}

		vector<T, 2> a;
		vector<T, 2> b;
	};

	template <typename T>
	struct matrix<T, 3>
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

		matrix(const vector<T, 3>& a, const vector<T, 3>& b, const vector<T, 3>& c)
		{
			this->a = a;
			this->b = b;
			this->c = c;
		}

		vector<T, 3>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<T, 3>& operator[] (uint8_t i) const
		{
			return (&a + i);
		}

		vector<T, 3> a;
		vector<T, 3> b;
		vector<T, 3> c;
	};

	template <typename T>
	struct matrix<T, 4>
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

		matrix(const vector<T, 4>& a, const vector<T, 4>& b, const vector<T, 4>& c, const vector<T, 4>& d)
		{
			this->a = a;
			this->b = b;
			this->c = c;
			this->d = d;
		}

		vector<T, 4> a;
		vector<T, 4> b;
		vector<T, 4> c;
		vector<T, 4> d;

		vector<T, 4>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		const vector<T, 4>& operator[] (uint8_t i) const
		{
			return *(&a + i);
		}
	};

	template <typename T, uint8_t N>
	matrix<T, N> operator*(matrix<T, N> a, matrix<T, N> b)
	{
		matrix<T, N> res;
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

	template <typename T, uint8_t N>
	vector<T, N> operator*(matrix<T, N> a, vector<T, N> b)
	{
		vector<T, N> res;
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