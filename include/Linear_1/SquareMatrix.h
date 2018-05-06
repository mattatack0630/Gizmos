//
// Created by mathew on 5/6/18.
//

#pragma once

#include "Matrix.h"

template<int N>
class SquareMatrix : public Matrix_T<N, N>
{
public:
	SquareMatrix();

	void set_identity();

	void set_transpose();
};

template<int N>
SquareMatrix<N>::SquareMatrix()
{

}

template<int N>
void SquareMatrix<N>::set_identity()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			float identity_value = (i == j) ? 1.0f : 0.0f;
			this->set_element(i, j, identity_value);
		}
	}
}

template<int N>
void SquareMatrix<N>::set_transpose()
{
	linear::transpose(*this, *this);
}
