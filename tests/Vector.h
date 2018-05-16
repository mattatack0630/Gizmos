//
// Created by mathew on 5/11/18.
//

#pragma once


#include "Matrix.h"

template<int N, typename T = float>
class Vector_T : public Matrix_T<1, N, T>
{
public:
	Vector_T();

	Vector_T(std::array<T, 1 * N> src);

	Vector_T(const Matrix_T<1, N, T>& src);

	inline void set_element(int n, T value) { this->elements[n] = value; }

	inline T get_element(int n) const { return this->elements[n]; }

	inline int get_size() const { return N; }
};

template<int N, typename T>
Vector_T<N, T>::Vector_T() :
		Matrix_T<1, N, T>()
{
}

template<int N, typename T>
Vector_T<N, T>::Vector_T(std::array<T, 1 * N> src):
		Matrix_T<1, N, T>(src)
{
}

template<int N, typename T>
Vector_T<N, T>::Vector_T(const Matrix_T<1, N, T>& src) :
		Matrix_T<1, N, T>(src)
{
}