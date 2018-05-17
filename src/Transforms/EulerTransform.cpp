//
// Created by mathew on 5/2/18.
//

#include <tgmath.h>
#include <Linear/Linear.h>
#include "Transforms/EulerTransform.h"

void EulerTransform::calculate_matrix(SquareMatrix<4>& dest)
{
	dest.set_identity();

	float cos_h = cos(rot_y);
	float cos_p = cos(rot_x);
	float cos_r = cos(rot_z);
	float sin_h = sin(rot_y);
	float sin_p = sin(rot_x);
	float sin_r = sin(rot_z);

	dest.set_element(0, 0, (cos_r * cos_h - sin_r * sin_p * sin_h));
	dest.set_element(0, 1, (sin_r * cos_h + cos_r * sin_p * sin_h));
	dest.set_element(0, 2, (-cos_p * sin_h));
	dest.set_element(1, 0, (-sin_r * cos_p));
	dest.set_element(1, 1, (cos_r * cos_p));
	dest.set_element(1, 2, (sin_p));
	dest.set_element(2, 0, (cos_r * sin_h + sin_r * sin_p * cos_h));
	dest.set_element(2, 1, (sin_r * sin_h - cos_r * sin_p * cos_h));
	dest.set_element(2, 2, (cos_p * cos_h));
}

void EulerTransform::calculate_matrix_inverse(SquareMatrix<4>& dest)
{
	dest.set_identity();

	const SquareMatrix<4> transform_matrix = Transform::get_matrix();

	// Orthogonal Euler matrix inverse is equal to transpose
	linear::transpose(transform_matrix, dest);
}

EulerTransform::EulerTransform(float x, float y, float z) :
		Transform(),
		rot_x(x),
		rot_y(y),
		rot_z(z)
{
	mark_for_update();
}

void EulerTransform::set_rotation(float x, float y, float z)
{
	rot_x = x;
	rot_y = y;
	rot_z = z;
	mark_for_update();
}
