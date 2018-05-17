//
// Created by mathew on 5/2/18.
//

#include <Linear/Linear.h>
#include "Transforms/WorldTransform.h"

WorldTransform::WorldTransform() :
		translation(0,0,0),
		rotation(0,0,0),
		scale(0,0,0)
{
	mark_for_update();
}

WorldTransform::WorldTransform(float p_x, float p_y, float p_z,
							   float r_x, float r_y, float r_z,
							   float s_x, float s_y, float s_z) :
		translation(p_x, p_y, p_z),
		rotation(r_x, r_y, r_z),
		scale(s_x, s_y, s_z)
{
	mark_for_update();
}

void WorldTransform::set_translation(float x, float y, float z)
{
	translation.set_translation(x, y, z);
	mark_for_update();
}

void WorldTransform::set_rotation(float x, float y, float z)
{
	rotation.set_rotation(x, y, z);
	mark_for_update();
}

void WorldTransform::set_scale(float x, float y, float z)
{
	scale.set_scale(x, y, z);
	mark_for_update();
}

void WorldTransform::calculate_matrix(SquareMatrix<4>& dest)
{
	dest.set_identity();
	linear::dot(translation.get_matrix(), rotation.get_matrix(), dest);
	linear::dot(dest, scale.get_matrix(), dest);
}

void WorldTransform::calculate_matrix_inverse(SquareMatrix<4>& dest)
{
	dest.set_identity();
	linear::dot(scale.get_matrix_inverse(), rotation.get_matrix_inverse(), dest);
	linear::dot(dest, translation.get_matrix_inverse(), dest);
}