#pragma once
#include "vector.h"
#include "matrix.h"
#include "quaternion.h"

namespace xm
{
	using vec2 = vector<2, float>;
	using vec3 = vector<3, float>;
	using vec4 = vector<4, float>;

	using mat2 = matrix<2, float>;
	using mat3 = matrix<3, float>;
	using mat4 = matrix<4, float>;

	using vec2i = vector<2, int>;
	using vec3i = vector<3, int>;
	using vec4i = vector<4, int>;

	using vec2d = vector<2, double>;
	using vec3d = vector<3, double>;
	using vec4d = vector<4, double>;

	using mat2d = matrix<2, double>;
	using mat3d = matrix<3, double>;
	using mat4d = matrix<4, double>;

	using quat = quaternion<float>;
	using quatd = quaternion<double>;
};