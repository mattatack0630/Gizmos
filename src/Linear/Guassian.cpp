//
// Created by mathew on 5/3/18.
//

#include <Linear/Guassian.h>
#include <cmath>

int find_pivot(Matrix& matrix, int col_on, int row_on)
{
	int pivot = -1;

	if (matrix.get_element(col_on, col_on) != 0) pivot = col_on;

	for (int y = 0; y < matrix.m_height && pivot == -1; y++) {
		if (y != row_on) {
			float element = matrix.get_element(col_on, y);
			if (element != 0) pivot = y;
		}
	}

	return pivot;
}

int find_lead(Matrix& matrix, int row)
{
	for (int x = 0; x < matrix.m_width; x++) {
		if (matrix.get_element(x, row) != 0) return x;
	}

	return -1;
}

void scale_leading_efficient(Matrix& matrix)
{
	for (int y = 0; y < matrix.m_height; y++) {
		float leading = 0;
		for (int x = 0; x < matrix.m_width; x++) {
			float element = floorf(matrix.get_element(x, y) * 10000) / 10000;
			if (element != 0) {
				if (leading == 0) leading = element;
				matrix.set_element(x, y, element / leading);
			}
		}
	}
}

void isolate_leading_efficient(Matrix& matrix)
{
	for (int x = 0; x < matrix.m_height; x++) {
		for (int y = matrix.m_height - 1; y >= 0; y--) {
			if (x != y) {
				int pivot = find_pivot(matrix, x, y);

				if (pivot != -1) {
					float scale = -1.0f / matrix.get_element(x, pivot) * matrix.get_element(x, y);
					std::cout<<matrix<<std::endl;
					Gaussian::row_operation_add_scaled_to(matrix, pivot, y, scale, matrix);
				}
			}
		}
	}
}

void order_by_leading_efficient(Matrix& matrix)
{
	// TODO Meh .. not now
}

void Gaussian::gaussian_reduce_echelon(Matrix& matrix, Matrix& dest)
{
	if (&matrix != &dest)
		Matrix::copy(matrix, dest);

	isolate_leading_efficient(dest);

	//scale_leading_efficient(dest);

	//order_by_leading_efficient(dest);
}

void Gaussian::row_operation_swap(Matrix const& left, int row1, int row2, Matrix& dest)
{
	// refine later
	if (&dest != &left) {
		for (int y = 0; y < dest.m_height; y++) {
			for (int x = 0; x < dest.m_width; x++) {
				dest.set_element(x, y, left.get_element(x, y));
			}
		}
	}

	for (int x = 0; x < dest.m_width; x++) {
		float temp = dest.get_element(x, row1);
		dest.set_element(x, row1, left.get_element(x, row2));
		dest.set_element(x, row2, temp);
	}
}

void Gaussian::row_operation_scale(Matrix const& left, int row, float scale, Matrix& dest)
{
	if (scale != 1.0f) {
		if (&left == &dest) {
			for (int i = 0; i < dest.m_width; i++) {
				dest.set_element(i, row, left.get_element(i, row) * scale);
			}
		} else {
			for (int j = 0; j < dest.m_height; j++) {
				for (int i = 0; i < dest.m_width; i++) {
					if (j == row) {
						float row_result = left.get_element(i, j) * scale;
						dest.set_element(i, j, row_result);
					} else {
						dest.set_element(i, j, left.get_element(i, j));
					}
				}
			}
		}
	}
}

void Gaussian::row_operation_add_to(Matrix const& left, int row1, int row2, Matrix& dest)
{
	if (row1 != row2) {
		if (&left == &dest) {
			for (int i = 0; i < dest.m_width; i++) {
				float row_result = left.get_element(i, row1) + left.get_element(i, row2);
				dest.set_element(i, row2, row_result);
			}
		} else {
			for (int j = 0; j < dest.m_height; j++) {
				for (int i = 0; i < dest.m_width; i++) {
					if (j == row2) {
						float row_result = left.get_element(i, j) + left.get_element(i, row1);
						dest.set_element(i, j, row_result);
					} else {
						dest.set_element(i, j, left.get_element(i, j));
					}
				}
			}
		}
	}
}

void Gaussian::row_operation_add_scaled_to(Matrix const& left, int row1, int row2, float scale, Matrix& dest)
{
	if (row1 != row2) {
		if (&left == &dest) {
			for (int i = 0; i < dest.m_width; i++) {
				float row_result = (left.get_element(i, row1) * scale) + left.get_element(i, row2);
				dest.set_element(i, row2, row_result);
			}
		} else {
			for (int j = 0; j < dest.m_height; j++) {
				for (int i = 0; i < dest.m_width; i++) {
					if (j == row2) {
						float row_result = left.get_element(i, j) + (left.get_element(i, row1) * scale);
						dest.set_element(i, j, row_result);
					} else {
						dest.set_element(i, j, left.get_element(i, j));
					}
				}
			}
		}
	}
}