//
// Created by mathew on 5/6/18.
//

#pragma once

#include "SquareMatrix.h"

class Matrix2f : public SquareMatrix<2>
{
public:
	Matrix2f();

	float determinate();
};

namespace linear
{
	float determinate_2x2(Matrix2f const& left);

	void invert_2x2(Matrix2f const& left, Matrix2f& dest);
};
