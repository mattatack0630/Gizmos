//
// Created by matthew on 8/8/17.
//

#pragma once

#include "Matrix.h"

class SquareMatrix : public Matrix
{
public:
	SquareMatrix(int s);

	void set_identity();

	void transpose();

	// Static Linear Algebra

//	static void invert_gaussian(Matrix const& left, Matrix& dest);
//	static void determinate(Matrix const& left, Matrix& dest);
};

