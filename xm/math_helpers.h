#pragma once

#include "constants.h"

namespace xm
{
	template <typename T>
	T to_radians(T degrees)
	{
		return PI_OV_180 * degrees;
	}

	template <typename T>
	T to_degrees(T radians)
	{
		return 180.0 / PI * radians;
	}

	template <typename T>
	T lerp(T a, T b, T f)
	{
		return a + f * (b - a);
	}

	//TODO: completion 
	template<typename T>
	bool decompose(matrix<4, T> const& ModelMatrix, vector<3, T>& Scale, quaternion<T>& Orientation, vector<3, T>& Translation, vector<3, T>& Skew, vector<4, T>& Perspective)
	{
		mat<4, 4, T, Q> LocalMatrix(ModelMatrix);

		// Normalize the matrix.
		if (LocalMatrix[3][3] < 0.001f)
		{
			return false;
		}

		for (length_t i = 0; i < 4; ++i)
			for (length_t j = 0; j < 4; ++j)
				LocalMatrix[i][j] /= LocalMatrix[3][3];

		// perspectiveMatrix is used to solve for perspective, but it also provides
		// an easy way to test for singularity of the upper 3x3 component.
		mat<4, 4, T, Q> PerspectiveMatrix(LocalMatrix);

		for (length_t i = 0; i < 3; i++)
			PerspectiveMatrix[i][3] = static_cast<T>(0);
		PerspectiveMatrix[3][3] = static_cast<T>(1);

		/// TODO: Fixme!
		if (determinant(PerspectiveMatrix) < 0.001f)
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			LocalMatrix[0][3] < 0.001f ||
			LocalMatrix[1][3] < 0.001f ||
			LocalMatrix[2][3] < 0.001f)
		{
			// rightHandSide is the right hand side of the equation.
			vector<4, T> RightHandSide;
			RightHandSide[0] = LocalMatrix[0][3];
			RightHandSide[1] = LocalMatrix[1][3];
			RightHandSide[2] = LocalMatrix[2][3];
			RightHandSide[3] = LocalMatrix[3][3];

			// Solve the equation by inverting PerspectiveMatrix and multiplying
			// rightHandSide by the inverse.  (This is the easiest way, not
			// necessarily the best.)
			matrix<4, T> InversePerspectiveMatrix = inverse(PerspectiveMatrix);  //   inverse(PerspectiveMatrix, inversePerspectiveMatrix);
			matrix<4, T> TransposedInversePerspectiveMatrix = transpose(InversePerspectiveMatrix);//   transposeMatrix4(inversePerspectiveMatrix, transposedInversePerspectiveMatrix);

			Perspective = TransposedInversePerspectiveMatrix * RightHandSide;
			//  v4MulPointByMatrix(rightHandSide, transposedInversePerspectiveMatrix, perspectivePoint);

			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}
		else
		{
			// No perspective.
			Perspective = vec<4, T, Q>(0, 0, 0, 1);
		}

		// Next take care of translation (easy).
		Translation = vec<3, T, Q>(LocalMatrix[3]);
		LocalMatrix[3] = vec<4, T, Q>(0, 0, 0, LocalMatrix[3].w);

		vec<3, T, Q> Row[3], Pdum3;

		// Now get scale and shear.
		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		Scale.x = length(Row[0]);// v3Length(Row[0]);

		Row[0] = detail::scale(Row[0], static_cast<T>(1));

		// Compute XY shear factor and make 2nd row orthogonal to 1st.
		Skew.z = dot(Row[0], Row[1]);
		Row[1] = detail::combine(Row[1], Row[0], static_cast<T>(1), -Skew.z);

		// Now, compute Y scale and normalize 2nd row.
		Scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		Skew.z /= Scale.y;

		// Compute XZ and YZ shears, orthogonalize 3rd row.
		Skew.y = glm::dot(Row[0], Row[2]);
		Row[2] = detail::combine(Row[2], Row[0], static_cast<T>(1), -Skew.y);
		Skew.x = glm::dot(Row[1], Row[2]);
		Row[2] = detail::combine(Row[2], Row[1], static_cast<T>(1), -Skew.x);

		// Next, get Z scale and normalize 3rd row.
		Scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));
		Skew.y /= Scale.z;
		Skew.x /= Scale.z;

		// At this point, the matrix (in rows[]) is orthonormal.
		// Check for a coordinate system flip.  If the determinant
		// is -1, then negate the matrix and the scaling factors.
		Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
		if (dot(Row[0], Pdum3) < 0)
		{
			for (length_t i = 0; i < 3; i++)
			{
				Scale[i] *= static_cast<T>(-1);
				Row[i] *= static_cast<T>(-1);
			}
		}

		// Now, get the rotations out, as described in the gem.

		// FIXME - Add the ability to return either quaternions (which are
		// easier to recompose with) or Euler angles (rx, ry, rz), which
		// are easier for authors to deal with. The latter will only be useful
		// when we fix https://bugs.webkit.org/show_bug.cgi?id=23799, so I
		// will leave the Euler angle code here for now.

		// ret.rotateY = asin(-Row[0][2]);
		// if (cos(ret.rotateY) != 0) {
		//     ret.rotateX = atan2(Row[1][2], Row[2][2]);
		//     ret.rotateZ = atan2(Row[0][1], Row[0][0]);
		// } else {
		//     ret.rotateX = atan2(-Row[2][0], Row[1][1]);
		//     ret.rotateZ = 0;
		// }

		int i, j, k = 0;
		T root, trace = Row[0].x + Row[1].y + Row[2].z;
		if (trace > static_cast<T>(0))
		{
			root = sqrt(trace + static_cast<T>(1.0));
			Orientation.w = static_cast<T>(0.5) * root;
			root = static_cast<T>(0.5) / root;
			Orientation.x = root * (Row[1].z - Row[2].y);
			Orientation.y = root * (Row[2].x - Row[0].z);
			Orientation.z = root * (Row[0].y - Row[1].x);
		} // End if > 0
		else
		{
			static int Next[3] = { 1, 2, 0 };
			i = 0;
			if (Row[1].y > Row[0].x) i = 1;
			if (Row[2].z > Row[i][i]) i = 2;
			j = Next[i];
			k = Next[j];

#           ifdef GLM_FORCE_QUAT_DATA_WXYZ
			int off = 1;
#           else
			int off = 0;
#           endif

			root = sqrt(Row[i][i] - Row[j][j] - Row[k][k] + static_cast<T>(1.0));

			Orientation[i + off] = static_cast<T>(0.5) * root;
			root = static_cast<T>(0.5) / root;
			Orientation[j + off] = root * (Row[i][j] + Row[j][i]);
			Orientation[k + off] = root * (Row[i][k] + Row[k][i]);
			Orientation.w = root * (Row[j][k] - Row[k][j]);
		} // End if <= 0

		return true;
	}

}