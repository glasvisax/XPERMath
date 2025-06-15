#include <iostream>

#include "Source/vector.h"
#include "Source/matrix.h"
#include "Source/matrix_transforms.h"
#include "Source/math_helpers.h"

using namespace xm;

using vec3 = vector<3, float>;
using mat4 = matrix<4, float>;

template <uint8_t N, typename T>
void printVector(vector<N, T> vec)
{
	const char* sep = "";
	for (int i = 0; i < N; ++i)
	{
		std::cout << sep << vec[i];
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
	printMatrix(eulRotZ<4>(to_radians(90.0f)));

	printMatrix(translate(mat4(1.0f), vec3(2.0f, 2.0f, 2.0f)));
}
