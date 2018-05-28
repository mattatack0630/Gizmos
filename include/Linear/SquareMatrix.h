//
// Created by mathew on 5/11/18.
//

#pragma once

#include "Matrix.h"

template<int N, typename T = float>
class SquareMatrix : public Matrix<N, N, T>
{
public:
	SquareMatrix();

	SquareMatrix(std::array<T, N * N> src);

	SquareMatrix(const Matrix<N, N, T>& src);

	void set_identity();
};


template<int N, typename T>
SquareMatrix<N, T>::SquareMatrix() :
		Matrix<N, N, T>()
{
}

template<int N, typename T>
SquareMatrix<N, T>::SquareMatrix(std::array<T, N * N> src):
		Matrix<N, N, T>(src)
{
}

template<int N, typename T>
SquareMatrix<N, T>::SquareMatrix(const Matrix<N, N, T>& src) :
		Matrix<N, N, T>(src)
{
}

template<int N, typename T>
void SquareMatrix<N, T>::set_identity()
{
	for(int x = 0; x<N; x++) {
		for (int y = 0; y < N; y++) {
			this->set_element(x, y, x == y ? 1 : 0);
		}
	}
}

typedef SquareMatrix<2, float> Matrix2f;
typedef SquareMatrix<3, float> Matrix3f;
typedef SquareMatrix<4, float> Matrix4f;
