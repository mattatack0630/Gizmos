//
// Created by mathew on 5/6/18.
//
#pragma once

#include "Transform.h"
#include "AABB.h"

class OrthoTransform : public Transform
{
private:
	AABB unit_bounds = AABB(-1, -1, -1, 1, 1, 1); // Change to center-extends format, not be used now
	AABB view_bounds;

protected:
	void calculate_matrix(SquareMatrix<4>& dest) override;

	void calculate_matrix_inverse(SquareMatrix<4>& dest) override;

public:

	OrthoTransform();

	OrthoTransform(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z);

	void set_unit_bounds(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z);

	void set_view_bounds(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z);
};
