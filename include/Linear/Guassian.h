//
// Created by mathew on 5/3/18.
//

#pragma once

#include <Linear/Matrix.h>

namespace Gaussian
{
	void gaussian_reduce_echelon(Matrix& matrix, Matrix& dest);

	void row_operation_swap(Matrix const& left, int row1, int row2, Matrix& dest);

	void row_operation_scale(Matrix const& left, int row1, float scale, Matrix& dest);

	void row_operation_add_to(Matrix const& left, int row1, int row2, Matrix& dest);

	void row_operation_add_scaled_to(Matrix const& left, int row1, int row2, float scale, Matrix& dest);
}