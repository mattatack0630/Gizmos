//
// Created by mathew on 5/2/18.
//

#include "Transforms/Transform.h"

void Transform::mark_for_update()
{
	transform.needs_update = true;
	transform_inverse.needs_update = true;
}

const SquareMatrix<4>& Transform::get_matrix()
{
	if (transform.needs_update) {
		calculate_matrix(transform.matrix);
		transform.needs_update = false;
	}

	return transform.matrix;
}

const SquareMatrix<4>& Transform::get_matrix_inverse()
{
	if (transform_inverse.needs_update) {
		calculate_matrix_inverse(transform_inverse.matrix);
		transform_inverse.needs_update = false;
	}

	return transform_inverse.matrix;
}