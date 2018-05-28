//
// Created by mathew on 5/6/18.
//

#include "Transforms/OrthoTransform.h"

OrthoTransform::OrthoTransform(float min_x, float min_y, float min_z,
											 float max_x, float max_y, float max_z) :
		view_bounds(min_x, min_y, min_z, max_x, max_y, max_z)
{
	mark_for_update();
}

OrthoTransform::OrthoTransform() :
		view_bounds(-1, -1, -1, 1, 1, 1)
{
	mark_for_update();
}

void OrthoTransform::set_unit_bounds(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z)
{
	unit_bounds.min_x = min_x;
	unit_bounds.min_y = min_y;
	unit_bounds.min_z = min_z;
	unit_bounds.max_x = max_x;
	unit_bounds.max_y = max_y;
	unit_bounds.max_z = max_z;

	Transform::mark_for_update();
}

void OrthoTransform::set_view_bounds(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z)
{
	view_bounds.min_x = min_x;
	view_bounds.min_y = min_y;
	view_bounds.min_z = min_z;
	view_bounds.max_x = max_x;
	view_bounds.max_y = max_y;
	view_bounds.max_z = max_z;

	Transform::mark_for_update();
}

void OrthoTransform::calculate_matrix(Matrix4f& dest)
{
	dest.set_identity();

	// Change to center-extends format
	dest.set_element(0, 0, (2.0f / (view_bounds.max_x - view_bounds.min_x)));
	dest.set_element(1, 1, (2.0f / (view_bounds.max_y - view_bounds.min_y)));
	dest.set_element(2, 2, (2.0f / (view_bounds.max_z - view_bounds.min_z))); // May be reversed

	//rethink this
	dest.set_element(3, 0, -((view_bounds.max_x + view_bounds.min_x) / (view_bounds.max_x - view_bounds.min_x)));
	dest.set_element(3, 1, -((view_bounds.max_y + view_bounds.min_y) / (view_bounds.max_y - view_bounds.min_y)));
	dest.set_element(3, 2, -((view_bounds.max_z + view_bounds.min_z) / (view_bounds.max_z - view_bounds.min_z)));
}

void OrthoTransform::calculate_matrix_inverse(Matrix4f& dest)
{
	dest.set_identity();

	// Change to center-extends format
	dest.set_element(0, 0, ((view_bounds.max_x - view_bounds.min_x) / 2.0f));
	dest.set_element(1, 1, ((view_bounds.max_y - view_bounds.min_y) / 2.0f));
	dest.set_element(2, 2, ((view_bounds.max_z - view_bounds.min_z) / 2.0f)); // May be reversed

	// rethink this
	dest.set_element(3, 0, ((view_bounds.max_x + view_bounds.min_x) / 2.0f));
	dest.set_element(3, 1, ((view_bounds.max_y + view_bounds.min_y) / 2.0f));
	dest.set_element(3, 2, ((view_bounds.max_z + view_bounds.min_z) / 2.0f));
}
