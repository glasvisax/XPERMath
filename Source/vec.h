#pragma once
#include <type_traits>

namespace xm 
{
	template <typename T, uint8_t N>
	struct vec;

	template<typename T>
	struct vec<T, 2> 
	{
		union
		{
			struct { T x, y };
			struct { T r, g };
			struct { T u, v };
		};
	};

	template<typename T>
	struct vec<T, 3>
	{
		union
		{
			struct { T x, y, z };
			struct { T r, g, b };
		};
	};
	

	template<typename T>
	struct vec<T, 3>
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
	};

}



