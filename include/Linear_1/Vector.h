//
// Created by mathew on 5/6/18.
//

#pragma once

#include <cmath>
#include "Matrix.h"

template<int N>
class Vector : public Matrix_T<1, N>
{
public:
	Vector();

	int get_size() const { return N; }

	inline float get_element(int i) const { return Matrix_T<1, N>::get_element(0, i); }

	inline void set_element(int i, float element) { Matrix_T<1, N>::set_element(0, i, element); }

	void set_normalized();

	void set_magnetude(float mag);

	float length_squared();

	float length();
};

/// Static Linear Algebra ///
namespace linear
{
	template<int N>
	float vector_dot(Vector<N> const& left, Vector<N> const& right);

	template<int N>
	void normalize(Vector<N> const& left, Vector<N>& dest);

	template<int N>
	void set_magnitude(Vector<N> const& left, float mag, Vector<N>& dest);

	template<int N>
	float length(Vector<N> const& left);

	template<int N>
	float length_squared(Vector<N> const& left);
};

/// Member Function Definitions ///
template<int N>
Vector<N>::Vector()
{

}

template<int N>
void Vector<N>::set_normalized()
{
	linear::normalize(*this, *this);
}

template<int N>
void Vector<N>::set_magnetude(float mag)
{
	linear::set_magnitude(*this, mag, *this);
}

template<int N>
float Vector<N>::length_squared()
{
	return linear::length(*this);
}

template<int N>
float Vector<N>::length()
{
	return linear::length(*this);
}

/// Operator Overloads ///
template<int N>
float operator*(Vector<N> const& left, Vector<N> const& right)
{
	return linear::vector_dot(left, right);
}

/// Linear Algebra Definitions ///

template<int N>
float linear::vector_dot(Vector<N> const& left, Vector<N> const& right)
{
	float value = 0;

	for (int k = 0; k < N; k++)
		value += (left.get_element(k) * right.get_element(k));

	return value;
}

template<int N>
void linear::normalize(Vector<N> const& left, Vector<N>& dest)
{
	float length = linear::length(left);
	linear::scale(left, (1.0f / length), dest);
}

template<int N>
void linear::set_magnitude(Vector<N> const& left, float mag, Vector<N>& dest)
{
	float length = linear::length(left);
	linear::scale(left, (mag / length), dest);
}

template<int N>
float linear::length(Vector<N> const& left)
{
	float lengthSqr = linear::length_squared(left);
	return sqrt(lengthSqr);
}

template<int N>
float linear::length_squared(Vector<N> const& left)
{
	float l = 0;

	for (int i = 0; i < left.get_size(); i++) {
		float v = left.get_element(i);
		l += (v * v);
	}

	return l;
}