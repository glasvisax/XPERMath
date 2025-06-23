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

	using ivec2 = vector<2, int>;
	using ivec3 = vector<3, int>;
	using ivec4 = vector<4, int>;

	using uvec2 = vector<2, unsigned int>;
	using uvec3 = vector<3, unsigned int>;
	using uvec4 = vector<4, unsigned int>;

	using dvec2 = vector<2, double>;
	using dvec3 = vector<3, double>;
	using dvec4 = vector<4, double>;

	using dmat2 = matrix<2, double>;
	using dmat3 = matrix<3, double>;
	using dmat4 = matrix<4, double>;

	using quat = quaternion<float>;
	using dquat = quaternion<double>;
};