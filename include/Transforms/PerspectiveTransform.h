//
// Created by mathew on 5/28/18.
//

#pragma once

#include "Transform.h"
#include "AABB.h"

class PerspectiveTransform : public Transform
{
private:
	AABB unit_bounds = AABB(-1, -1, -1, 1, 1, 1); // Change to center-extends format, not be used now

	float aspect_ratio;
	float near;
	float far;
	float fov;

protected:
	void calculate_matrix(Matrix4f& dest) override;

	void calculate_matrix_inverse(Matrix4f& dest) override;

public:

	PerspectiveTransform();

	PerspectiveTransform(float aspect_ratio, float near, float far, float fov);

	void set_view_frustum(float aspect_ratio, float near, float far, float fov);
};
