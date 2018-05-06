//
// Created by mathew on 5/6/18.
//

#pragma once


#include "SquareMatrix.h"

class Matrix3f : public SquareMatrix<3>
{
public:
	Matrix3f();

	float determinate();
};

namespace linear
{
	float determinate_3x3(Matrix3f const& left);

	void invert_3x3(Matrix3f const& left, Matrix3f& dest);
};
