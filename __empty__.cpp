#include <iostream>

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
	xm::vec3 m_position{ 0.0f, 0.0f, 0.0f };

	xm::vec3 m_look_dir{ 0.0f, 0.0f, 1.0f };
	xm::vec3 m_right{ 1.0f, 0.0f, 0.0f };
	xm::vec3 m_up{ 0.0f, 1.0f, 0.0f };

	xm::vec3 m_world_up{ 0.0f, 1.0f, 0.0f };

	auto [m, x, y] = lookAtRH(m_position, m_look_dir, m_world_up);


	//vector<3, float> f(normalize(look_dir));
	//vector<3, float> s(normalize(cross(f, world_up)));
	//vector<3, float> u(cross(s, f));
	//f = -f;

	//vector<3, float> z = normalize(-look_dir);
	//vector<3, float> x = normalize(crossRH(world_up, -look_dir));
	//vector<3, float> y = normalize(crossRH(-look_dir, x));


}
