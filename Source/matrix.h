#include "vector.h"

namespace xm 
{
	template <typename T, uint8_t N>
	struct matrix;
	
	template <typename T>
	struct matrix<T, 2>
	{
		static_assert(std::is_floating_point_v<T>);
		vector<T, 2> a;
		vector<T, 2> b;

		vector<T, 4>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		vector<T, 4> operator[] (uint8_t i) const
		{
			return (&a + i);
		}
	};

	template <typename T>
	struct matrix<T, 3>
	{
		static_assert(std::is_floating_point_v<T>);
		vector<T, 3> a;
		vector<T, 3> b;
		vector<T, 3> c;

		vector<T, 4>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		vector<T, 4> operator[] (uint8_t i) const
		{
			return (&a + i);
		}
	};

	template <typename T>
	struct matrix<T, 4>
	{
		static_assert(std::is_floating_point_v<T>);

		vector<T, 4> a;
		vector<T, 4> b;
		vector<T, 4> c;
		vector<T, 4> d;

		vector<T, 4>& operator[] (uint8_t i)
		{
			return *(&a + i);
		}

		vector<T, 4> operator[] (uint8_t i) const
		{
			return *(&a + i);
		}
	};
}