//
// Created by mathew on 5/2/18.
//

#pragma once

#include <Linear/SquareMatrix.h>

struct UpdateMatrix
{
	SquareMatrix<4> matrix;
	bool needs_update;
};

class Transform
{
private:
	UpdateMatrix transform;
	UpdateMatrix transform_inverse;

protected:
	void mark_for_update();

	virtual void calculate_matrix(SquareMatrix<4>& dest) = 0;

	virtual void calculate_matrix_inverse(SquareMatrix<4>& dest) = 0;

public:
	const SquareMatrix<4>& get_matrix();

	const SquareMatrix<4>& get_matrix_inverse();
};
