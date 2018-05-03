//
// Created by matthew on 8/8/17.
//

#pragma once

#include "Matrix.h"

class Vector : public Matrix
{
public:
	Vector(int s);

	int get_size() const { return m_height; }

	inline float get_element(int i) const { return m_elementArray[i][0]; }

	inline void set_element(int i, float element) { m_elementArray[i][0] = element; }

	void normalize();

	void set_magnetude(float mag);

	float length_squared();

	float length();

	// Static Linear Algebra

	static void normalize(Vector const& left, Vector& dest);

	static void set_magnitude(Vector const& left, float mag, Vector& dest);

	static float dot(Vector const& left, Vector const& right);

	static float angle(Vector const& left, Vector const& right); // Maybe remove, this has no meaning for most vectors

	static float length_squared(Vector const& left);

	static float length(Vector const& left);
};

float operator*(Vector const& left, Vector const& right); //dot
