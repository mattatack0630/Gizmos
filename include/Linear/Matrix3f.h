//
// Created by matthew on 8/9/17.
//

#pragma once

#include "SquareMatrix.h"

class Matrix3f : public SquareMatrix
{
public:
	Matrix3f();

	static float determinate_3x3(Matrix3f const& left);

	static void invert_3x3(Matrix3f const& left, Matrix3f& dest);
};


