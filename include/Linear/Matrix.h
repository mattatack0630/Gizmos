//
// Created by matthew on 8/7/17.
//

#pragma once

#include <iostream>
#include <vector>

class Matrix
{
protected:
	// Stored [row][column] or [y][x]
	std::vector<std::vector<float>> m_elementArray;

public:
	int m_width;
	int m_height;

	Matrix(int w, int h);

	Matrix(const Matrix& src);

	inline void set_element(int x, int y, float value) { m_elementArray[y][x] = value; }

	inline float get_element(int x, int y) const { return m_elementArray[y][x]; }

	void set_zero();

	//Static Linear Algebra

	static void copy(Matrix const& left, Matrix& dest);

	static bool are_equal(Matrix const& left, Matrix const& right, float tolerance = 0.0f);

	static void component_mult(Matrix const& left, Matrix const& right, Matrix& dest);

	static void component_div(Matrix const& left, Matrix const& right, Matrix& dest);

	static void sub(Matrix const& left, Matrix const& right, Matrix& dest);

	static void add(Matrix const& left, Matrix const& right, Matrix& dest);

	static void dot(Matrix const& left, Matrix const& right, Matrix& dest);

	static void scale(Matrix const& left, float scale, Matrix& dest);

	static void transpose(Matrix const& left, Matrix& dest);

	static void negate(Matrix const& left, Matrix& dest);

	static void abs(Matrix const& left, Matrix& dest);
};

// Operator overloads
std::ostream& operator<<(std::ostream& os, Matrix const& left); // add
bool operator==(Matrix const& left, Matrix const& right); // compare
bool operator!=(Matrix const& left, Matrix const& right); // compare
Matrix operator+(Matrix const& left, Matrix const& right); // add
Matrix operator-(Matrix const& left, Matrix const& right); // sub
Matrix operator*(Matrix const& left, Matrix const& right); //dot
