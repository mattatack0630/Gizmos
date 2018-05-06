//
// Created by matthew on 8/9/17.
//

#pragma once


#include "SquareMatrix.h"

class Matrix2f : public SquareMatrix
{
public:
	Matrix2f();

	static float determinate_2x2(Matrix2f const& left);

	static void invert_2x2(Matrix2f const& left, Matrix2f& dest);
};


