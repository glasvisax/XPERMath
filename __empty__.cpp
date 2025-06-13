#include <iostream>

#include "Source/vector.h"
#include "Source/matrix.h"
#include "Source/matrix_transforms.h"
#include "Source/math_helpers.h"

using namespace xm;

using vec3 = vector<float, 3>;
template <typename T, uint8_t N>
void printVector(vector<T, N> vec)
{
	const char* sep = "";
	for (int i = 0; i < N; ++i)
	{
		std::cout << sep << vec[i];
		sep = ", ";
	}
	std::cout << "\n";
}

template <typename T, uint8_t N>
void printMatrix(matrix<T, N> mat)
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

	printMatrix(eulRotZ(to_radians(90.0f)));

}
