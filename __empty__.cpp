#include <iostream>
#include <iomanip>
#include "xm/vector.h"
#include "xm/matrix.h"
#include "xm/matrix_transforms.h"
#include "xm/math_helpers.h"
#include "xm/typedefs.h"

using namespace xm;

using vec3 = vector<3, float>;
using mat4 = matrix<4, float>;

template <uint8_t N, typename T>
void printVector(vector<N, T> vec)
{
	const char* sep = "";
	for (int i = 0; i < N; ++i)
	{
		std::cout << std::fixed << std::setprecision(1) << sep << vec[i];
		sep = ", ";
	}
	std::cout << "\n";
}

template <uint8_t N, typename T>
void printMatrix(matrix<N, T> mat)
{
	const char* sep = "";
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << mat[j][i] << " ";
		}
		std::cout << "\n";
	}
}

void main()
{
	xm::vec3 Look{ 0.0f, 0.0f, -1.0f };

	xm::mat3 rotx = eulRotX<3>(to_radians(90.0f));
	xm::mat3 roty = eulRotY<3>(to_radians(90.0f));

	xm::mat3 rotation = roty * rotx;

	xm::vec3 new_Look = rotation * Look;

	printVector(new_Look);
}
