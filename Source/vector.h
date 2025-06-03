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
		union
		{
			struct { T x, y };
			struct { T r, g };
			struct { T u, v };
		};

		T& operator[](uint8_t i) 
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}

	};

	template<typename T>
	struct vector<T, 3>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);
		union
		{
			struct { T x, y, z };
			struct { T r, g, b };
		};

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}
	};
	

	template<typename T>
	struct vector<T, 3>
	{
		static_assert(std::is_floating_point_v<T> || std::is_integral_v<T>);
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		T& operator[](uint8_t i)
		{
			return *(&x + i);
		}

		T operator[](uint8_t i) const
		{
			return *(&x + i);
		}
	};
}



