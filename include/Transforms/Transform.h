//
// Created by mathew on 5/2/18.
//

#pragma once

#include <Linear/Matrix4f.h>

struct UpdateMatrix
{
	Matrix4f matrix;
	bool needs_update;
};

class Transform
{
private:
	UpdateMatrix transform;
	UpdateMatrix transform_inverse;

protected:
	void mark_for_update();

	virtual void calculate_matrix(Matrix4f& dest) = 0;

	virtual void calculate_matrix_inverse(Matrix4f& dest) = 0;

public:
	const Matrix4f& get_matrix();

	const Matrix4f& get_matrix_inverse();
};
