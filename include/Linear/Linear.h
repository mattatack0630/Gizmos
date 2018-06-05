//
// Created by mathew on 5/8/18.
//

#pragma once

#include "Matrix.h"
#include <cmath>


namespace linear
{
	template<int CV, int DW, int DH, typename T>
	void dot(Matrix<CV, DH, T> const& left, Matrix<DW, CV, T> const& right, Matrix<DW, DH, T>& dest);

	template<int W, int H, typename T>
	void component_mult(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void component_div(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void add(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void sub(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void scale(Matrix<W, H, T> const& left, float scale, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void transpose(Matrix<W, H, T> const& left, Matrix<H, W, T>& dest);

	template<int W, int H, typename T>
	void negate(Matrix<W, H, T> const& left, Matrix<W, H, T>& dest);

	template<int W, int H, typename T>
	void abs(Matrix<W, H, T> const& left, Matrix<W, H, T>& dest);

	template<int N, typename T>
	float determinate(Matrix<N, N, T> const& left);

	template<typename T>
	float determinate(Matrix<2, 2, T> const& left);

	template<typename T>
	float determinate(Matrix<3, 3, T> const& left);

	template<int W, int H, typename T>
	void inner_matrix(Matrix<W, H, T> const& left, int leap_x, int leap_y, Matrix<W - 1, H - 1, T>& dest);

	template<int N, typename T>
	void minors_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest);

	template<int N, typename T>
	void cofactors_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest);

	template<int N, typename T>
	void adjoint_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest);

	template<int N, typename T>
	void adjoint_invert(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest);

	template<typename T>
	void invert(const Matrix<3, 3, T>& left, Matrix<3, 3, T>& dest);

	template<typename T>
	void invert(const Matrix<2, 2, T>& left, Matrix<2, 2, T>& dest);

	template<typename T>
	void cross(Matrix<1, 3, T> const& left, Matrix<1, 3, T> const& right, Matrix<1, 3, T>& dest);

	template<typename T, int N>
	float length(Matrix<1, N, T> const& left);

	template<typename T, int N>
	float lengthSquared(Matrix<1, N, T> const& left);

	template<typename T, int N>
	void normalize(Matrix<1, N, T> const& left, Matrix<1, N, T>& dest);
}

template<int CV, int DW, int DH, typename T>
void linear::dot(Matrix<CV, DH, T> const& left, Matrix<DW, CV, T> const& right, Matrix<DW, DH, T>& dest)
{
	std::array<T, DW * DH> t_elements;

	for (int y = 0; y < DH; y++) {
		for (int x = 0; x < DW; x++) {
			float elementVal = 0;

			for (int k = 0; k < CV; k++)
				elementVal += (left.get_element(k, y) * right.get_element(x, k));

			t_elements[x * dest.get_height() + y] = elementVal;
		}
	}

	dest.set_elements(t_elements);
}

template<int W, int H, typename T>
void linear::component_mult(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * right.get_element(i, j));
		}
	}
}

template<int W, int H, typename T>
void linear::component_div(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) / right.get_element(i, j));
		}
	}
}

template<int W, int H, typename T>
void linear::add(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) + right.get_element(i, j));
		}
	}
}

template<int W, int H, typename T>
void linear::sub(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) - right.get_element(i, j));
		}
	}
}

template<int W, int H, typename T>
void linear::scale(Matrix<W, H, T> const& left, float scale, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * scale);
		}
	}
}

template<int W, int H, typename T>
void linear::transpose(Matrix<W, H, T> const& left, Matrix<H, W, T>& dest)
{
	std::array<T, W * H> t_elements;

	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			t_elements[x * H + y] = left.get_element(y, x);
		}
	}

	dest.set_elements(t_elements);
}

template<int W, int H, typename T>
void linear::negate(Matrix<W, H, T> const& left, Matrix<W, H, T>& dest)
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * -1);
		}
	}
}

template<int N, typename T>
float linear::determinate(Matrix<N, N, T> const& left)
{
	//std::cout << "DET GENERAL" << std::endl;

	Matrix<N, N, T> cofactors = Matrix<N, N, T>(); // Remove these
	linear::cofactors_matrix(left, cofactors); // Dont need entire thing!

	float det = 0;
	for (int i = 0; i < N; i++) {
		det += (left.get_element(0, i) * cofactors.get_element(0, i));
	}

	return det;
}

template<typename T>
float linear::determinate(Matrix<2, 2, T> const& left)
{
	//std::cout << "DET SPECIAL 2" << std::endl;

	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(0, 1);
	float d = left.get_element(1, 1);
	float result = a * d - c * b;
	return result;
}

template<typename T>
float linear::determinate(Matrix<3, 3, T> const& left)
{
	//std::cout << "DET SPECIAL 3" << std::endl;

	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(2, 0);
	float d = left.get_element(0, 1);
	float e = left.get_element(1, 1);
	float f = left.get_element(2, 1);
	float g = left.get_element(0, 2);
	float h = left.get_element(1, 2);
	float i = left.get_element(2, 2);
	float result = (a * e * i) + (b * f * g) + (c * d * h) - (g * e * c) - (h * f * a) - (i * d * b);
	return result;
}

template<int W, int H, typename T>
void linear::inner_matrix(const Matrix<W, H, T>& left, int leap_x, int leap_y, Matrix<W - 1, H - 1, T>& dest)
{
	float dest_x = 0;

	for (int i = 0; i < W; i++) {
		if (i != leap_x) {
			float dest_y = 0;

			for (int j = 0; j < H; j++) {
				if (j != leap_y) {
					dest.set_element(dest_x, dest_y, left.get_element(i, j));
					dest_y++;
				}
			}

			dest_x++;
		}
	}
}

template<int N, typename T>
void linear::minors_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest)
{
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			Matrix<N - 1, N - 1, T> inner = Matrix<N - 1, N - 1, T>();
			linear::inner_matrix(left, x, y, inner);
			float det = linear::determinate(inner);
			dest.set_element(x, y, det);
		}
	}
}

template<int N, typename T>
void linear::cofactors_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest)
{
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			Matrix<N - 1, N - 1, T> inner = Matrix<N - 1, N - 1, T>(); // Remove these
			linear::inner_matrix(left, x, y, inner);
			float cof_coeffient = ((x + y) % 2 == 0 ? 1 : -1);
			float det = linear::determinate(inner);
			dest.set_element(x, y, det * cof_coeffient);
		}
	}
}

template<int N, typename T>
void linear::adjoint_matrix(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest)
{
	linear::cofactors_matrix(left, dest);
	linear::transpose(dest, dest);
}

template<int N, typename T>
void linear::adjoint_invert(const Matrix<N, N, T>& left, Matrix<N, N, T>& dest)
{
	linear::adjoint_matrix(left, dest);

	float det = 0;
	for (int i = 0; i < N; i++)
		det += dest.get_element(0, i) * left.get_element(i, 0);
	det = (det == 0.0f) ? (0.0f) : (1.0f / det);

	linear::scale(dest, det, dest);
}

template<typename T>
void linear::invert(const Matrix<3, 3, T>& left, Matrix<3, 3, T>& dest)
{
	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(2, 0);
	float d = left.get_element(0, 1);
	float e = left.get_element(1, 1);
	float f = left.get_element(2, 1);
	float g = left.get_element(0, 2);
	float h = left.get_element(1, 2);
	float i = left.get_element(2, 2);
	float det = (a * e * i) + (b * f * g) + (c * d * h) - (g * e * c) - (h * f * a) - (i * d * b);

	if (det != 0) {
		dest.set_element(0, 0, (e * i - f * h) / det);
		dest.set_element(1, 0, -(g * i - c * h) / det);
		dest.set_element(2, 0, (b * f - c * e) / det);
		dest.set_element(0, 1, -(d * i - f * g) / det);
		dest.set_element(1, 1, (a * i - c * g) / det);
		dest.set_element(2, 1, -(a * f - c * d) / det);
		dest.set_element(0, 2, (d * h - e * g) / det);
		dest.set_element(1, 2, -(a * h - b * g) / det);
		dest.set_element(2, 2, (a * e - b * d) / det);
	} else {
		// throw div by zero exe
		linear::scale(dest, 0.0f, dest);
	}
}

template<typename T>
void linear::invert(const Matrix<2, 2, T>& left, Matrix<2, 2, T>& dest)
{
	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(0, 1);
	float d = left.get_element(1, 1);
	float det = a * d - c * b;

	if (det != 0) {
		dest.set_element(0, 0, d / det);
		dest.set_element(1, 0, -b / det);
		dest.set_element(0, 1, -c / det);
		dest.set_element(1, 1, a / det);
	} else {
		// throw div by zero exe
		linear::scale(dest, 0.0f, dest);
	}
}

template<typename T, int N>
float linear::length(const Matrix<1, N, T>& left)
{
	float square_len = linear::lengthSquared(left);
	float length = sqrt(square_len);
	return length;
}

template<typename T, int N>
float linear::lengthSquared(const Matrix<1, N, T>& left)
{
	float add = 0;

	for (int i = 0; i < N; i++)
		add += (float) left.get_element(0, i);

	return add;
}

template<typename T, int N>
void linear::normalize(const Matrix<1, N, T>& left, Matrix<1, N, T>& dest)
{
	float length = linear::length(left);
	linear::scale(left, 1.0 / length, dest);
}

template<typename T>
void linear::cross(Matrix<1, 3, T> const& left, Matrix<1, 3, T> const& right, Matrix<1, 3, T>& dest)
{
	float l_x = left.get_element(0, 0);
	float l_y = left.get_element(0, 1);
	float l_z = left.get_element(0, 2);
	float r_x = right.get_element(0, 0);
	float r_y = right.get_element(0, 1);
	float r_z = right.get_element(0, 2);
	dest.set_element(0, 0, (l_y * r_z) - (l_z * r_y));
	dest.set_element(0, 1, (l_z * r_x) - (l_x * r_z));
	dest.set_element(0, 2, (l_x * r_y) - (l_y * r_x));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<int CV, int DW, int DH, typename T>
Matrix<DW, DH, T> operator*(Matrix<CV, DH, T> const& left, Matrix<DW, CV, T> const& right)
{
	Matrix<DW, DH, T> dest = Matrix<DW, DH, T>();

	linear::dot(left, right, dest);

	return dest;
}

template<int W, int H, typename T>
Matrix<W, H, T>operator+(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right)
{
	Matrix<W,H,T> dest = Matrix<W, H, T>();
	linear::add(left, right, dest);
	return dest;

}

template<int W, int H, typename T>
Matrix<W, H, T> operator-(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right)
{
	Matrix<W,H,T> dest = Matrix<W, H, T>();
	linear::sub(left, right, dest);
	return dest;

}

template<int W, int H, typename T>
Matrix<W, H, T> operator*(Matrix<W, H, T> const& left, float scale)
{
	Matrix<W,H,T> dest = Matrix<W, H, T>();
	linear::scale(left, scale, dest);
	return dest;

}

template<int W, int H, typename T>
void operator*=(Matrix<W, H, T>& left, Matrix<W, H, T> const& right)
{
	linear::dot(left, right, left);
}

template<int W, int H, typename T>
void operator+=(Matrix<W, H, T>& left, Matrix<W, H, T> const& right)
{
	linear::add(left, right, left);
}

template<int W, int H, typename T>
void operator-=(Matrix<W, H, T>& left, Matrix<W, H, T> const& right)
{
	linear::sub(left, right, left);
}

template<int W, int H, typename T>
void operator*=(Matrix<W, H, T>& left, float scale)
{
	linear::scale(left, scale, left);
}

template<int W, int H, typename T>
void operator/=(Matrix<W, H, T>& left, float scale)
{
	linear::scale(left, 1.0f/scale, left);
}