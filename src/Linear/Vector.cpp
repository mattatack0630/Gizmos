//
// Created by matthew on 8/8/17.
//

#include "Linear/Vector.h"
#include <cmath>

Vector::Vector(int s) : Matrix(1, s)
{

}

void Vector::set_magnetude(float mag)
{
	Vector::set_magnitude(*this, mag, *this);
}

void Vector::normalize()
{
	Vector::normalize(*this, *this);
}

float Vector::length_squared()
{
	return Vector::length_squared(*this);
}

float Vector::length()
{
	return Vector::length(*this);
}

// Operator Overloading

float operator*(Vector const &left, Vector const &right)
{
	return Vector::dot(left, right);
}

// Vector Algebra

void Vector::normalize(Vector const &left, Vector &dest)
{
	float length = Vector::length(left);
	Matrix::scale(left, (1.0f / length), dest);
}

void Vector::set_magnitude(Vector const& left, float mag, Vector& dest)
{
	float length = Vector::length(left);
	Matrix::scale(left, (mag / length), dest);
}

float Vector::dot(Vector const &left, Vector const &right)
{
	// Error check : must have same size vectors
	float d = 0;

	for (int i = 0; i < left.get_size(); i++)
		d += left.get_element(i) * right.get_element(i);

	return d;
}

float Vector::angle(Vector const &left, Vector const &right)
{
	float ll = Vector::length(left);
	float rl = Vector::length(right);
	float dls = Vector::dot(left, right) / (ll * rl);

	// Clamp dls to (-1, 1)
	dls = (dls <= -1 ? -1 : dls >= 1 ? 1 : dls);

	return acos(dls);
}

float Vector::length_squared(Vector const& left)
{
	float l = 0;

	for (int i = 0; i < left.get_size(); i++)
	{
		float v = left.get_element(i);
		l += (v * v);
	}

	return l;
}

float Vector::length(Vector const &left)
{
	float lengthSqr = Vector::length_squared(left);
	return sqrt(lengthSqr);
}
