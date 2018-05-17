//
// Created by mathew on 5/2/18.
//

#include "Transforms/ScaleTransform.h"

void ScaleTransform::calculate_matrix(SquareMatrix<4>& dest)
{
	dest.set_identity();
	dest.set_element(0, 0, scale_x);
	dest.set_element(1, 1, scale_y);
	dest.set_element(2, 2, scale_z);
}

void ScaleTransform::calculate_matrix_inverse(SquareMatrix<4>& dest)
{
	// TODO cannot enter 0 scale error
	dest.set_identity();
	dest.set_element(0, 0, 1 / scale_x);
	dest.set_element(1, 1, 1 / scale_y);
	dest.set_element(2, 2, 1 / scale_z);
}

ScaleTransform::ScaleTransform(float x, float y, float z) :
		Transform(),
		scale_x(x),
		scale_y(y),
		scale_z(z)
{
	mark_for_update();
}

void ScaleTransform::set_scale(float x, float y, float z)
{
	scale_x = x;
	scale_y = y;
	scale_z = z;
	mark_for_update();
}

