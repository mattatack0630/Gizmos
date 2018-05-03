//
// Created by matthew on 8/8/17.
//

#include "Linear/SquareMatrix.h"

SquareMatrix::SquareMatrix(int s) : Matrix(s, s)
{

}

void SquareMatrix::set_identity()
{
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			float identity_value = (i == j) ? 1.0f : 0.0f;
			set_element(i, j, identity_value);
		}
	}
}

void SquareMatrix::transpose()
{
	Matrix::transpose(*this, *this);
}
