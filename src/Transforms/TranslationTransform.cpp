//
// Created by mathew on 5/2/18.
//

#include "Transforms/TranslationTransform.h"


void TranslationTransform::calculate_matrix(Matrix4f& dest)
{
	dest.set_identity();
	dest.set_element(3, 0, position_x);
	dest.set_element(3, 1, position_y);
	dest.set_element(3, 2, position_z);
}

void TranslationTransform::calculate_matrix_inverse(Matrix4f& dest)
{
	dest.set_identity();
	dest.set_element(3, 0, -position_x);
	dest.set_element(3, 1, -position_y);
	dest.set_element(3, 2, -position_z);
}

TranslationTransform::TranslationTransform(float x, float y, float z) :
		Transform(),
		position_x(x),
		position_y(y),
		position_z(z)
{
	mark_for_update();
}

void TranslationTransform::set_translation(float x, float y, float z)
{
	position_x = x;
	position_y = y;
	position_z = z;
	mark_for_update();
}

