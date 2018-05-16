//
// Created by mathew on 5/11/18.
//

#pragma once

#include "Matrix.h"

template<int N, typename T = float>
class SquareMatrix_T : public Matrix_T<N, N, T>
{
public:
	SquareMatrix_T();

	SquareMatrix_T(std::array<T, N*N> src);

	SquareMatrix_T(const Matrix_T<N, N, T>& src);
};


template<int N, typename T>
SquareMatrix_T<N, T>::SquareMatrix_T() :
		Matrix_T<N, N, T>()
{
}

template<int N, typename T>
SquareMatrix_T<N, T>::SquareMatrix_T(std::array<T, N * N> src):
		Matrix_T<N, N, T>(src)
{
}

template<int N, typename T>
SquareMatrix_T<N, T>::SquareMatrix_T(const Matrix_T<N, N, T>& src) :
		Matrix_T<N, N, T>(src)
{
}