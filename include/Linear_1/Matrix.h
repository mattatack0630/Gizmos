//
// Created by mathew on 5/4/18.
//

#pragma once

#include <array>
#include <iomanip>
#include <iostream>

template<int W, int H>
class Matrix_T
{
private:
	// Stored [column][row] or [x][y] or y*width+x
	std::array<float, W * H> elements = {};

public:
	Matrix_T();

	Matrix_T(const Matrix_T<W, H>& src);

	inline void set_elements(std::array<float, W * H> src) { std::copy(std::begin(src), std::end(src), std::begin(elements)); }

	inline void set_element(int x, int y, float value) { elements[y * W + x] = value; }

	inline float get_element(int x, int y) const { return elements[y * W + x]; }

	inline int get_height() const { return H; }

	inline int get_width() const { return W; }

	bool is_equal(Matrix_T<W, H> matrix, float tolerance = 0.0f) const;
};

namespace linear
{
	template<int CV, int DW, int DH>
	void dot(Matrix_T<CV, DH> const& left, Matrix_T<DW, CV> const& right, Matrix_T<DW, DH>& dest);

	template<int W, int H>
	void add(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest);

	template<int W, int H>
	void component_mult(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest);

	template<int W, int H>
	void component_div(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest);

	template<int W, int H>
	void sub(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest);

	template<int W, int H>
	void scale(Matrix_T<W, H> const& left, float scale, Matrix_T<W, H>& dest);

	template<int W, int H>
	void transpose(Matrix_T<W, H> const& left, Matrix_T<H, W>& dest);

	template<int W, int H>
	void negate(Matrix_T<W, H> const& left, Matrix_T<W, H>& dest);

	template<int W, int H>
	void abs(Matrix_T<W, H> const& left, Matrix_T<W, H>& dest);
}


/// Member Function Definitions ///

template<int W, int H>
Matrix_T<W, H>::Matrix_T() :
		elements({})
{
}

template<int W, int H>
Matrix_T<W, H>::Matrix_T(const Matrix_T<W, H>& src) :
		elements(src.elements)
{
}

template<int W, int H>
bool Matrix_T<W, H>::is_equal(Matrix_T<W, H> matrix, float tolerance) const
{
	bool equal = true;

	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			float diff = (get_element(x, y) - matrix.get_element(x, y));
			diff *= diff >= 0 ? 1 : -1;
			equal &= (diff <= tolerance);
		}
	}

	return equal;
}

///    Overloaded Operators    ///

template<int W, int H>
std::ostream& operator<<(std::ostream& os, Matrix_T<W, H> const& matrix)
{
	os.precision(3);

	std::cout << "test" << std::endl;

	for (int j = 0; j < H; j++) {
		os << "[";

		for (int i = 0; i < W; i++) {
			if (i != W - 1)
				os << std::left << std::setw(10);
			os << std::fixed << matrix.get_element(i, j);
		}

		os << "]";
		os << std::endl;
	}

	return os;
}

template<int W, int H>
bool operator==(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right)
{
	return left.is_equal(right);
}

template<int W, int H>
bool operator!=(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right)
{
	return !left.is_equal(right);
}

template<int W, int H>
Matrix_T<W, H> operator+(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right)
{
	Matrix_T<W, H> dest;

	linear::add(left, right, dest);

	return dest;
}

template<int W, int H>
Matrix_T<W, H> operator-(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right)
{
	Matrix_T<W, H> dest;

	linear::sub(left, right, dest);

	return dest;
}

template<int CV, int DW, int DH>
Matrix_T<DW, DH> operator*(Matrix_T<CV, DH> const& left, Matrix_T<DW, CV> const& right)
{
	Matrix_T<DW, DH> dest;

	linear::dot(left, right, dest);

	return dest;
}


///  Generic Algebra Methods  ///

template<int CV, int DW, int DH>
void linear::dot(Matrix_T<CV, DH> const& left, Matrix_T<DW, CV> const& right, Matrix_T<DW, DH>& dest)
{
	std::array<float, DW * DH> t_elements;

	for (int y = 0; y < DH; y++) {
		for (int x = 0; x < DW; x++) {
			float elementVal = 0;

			for (int k = 0; k < CV; k++)
				elementVal += (left.get_element(k, y) * right.get_element(x, k));

			t_elements[y * dest.get_width() + x] = elementVal;
		}
	}

	dest.set_elements(t_elements);
}

template<int W, int H>
void linear::component_mult(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * right.get_element(i, j));
		}
	}
}

template<int W, int H>
void linear::component_div(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) / right.get_element(i, j));
		}
	}
}

template<int W, int H>
void linear::add(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) + right.get_element(i, j));
		}
	}
}

template<int W, int H>
void linear::sub(Matrix_T<W, H> const& left, Matrix_T<W, H> const& right, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) - right.get_element(i, j));
		}
	}
}

template<int W, int H>
void linear::scale(Matrix_T<W, H> const& left, float scale, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * scale);
		}
	}
}

template<int W, int H>
void linear::transpose(Matrix_T<W, H> const& left, Matrix_T<H, W>& dest)
{
	//TODO make 1D
	float t_elements[H][W];

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			t_elements[j][i] = left.get_element(i, j);
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			dest.set_element(i, j, t_elements[i][j]);
		}
	}
}

template<int W, int H>
void linear::negate(Matrix_T<W, H> const& left, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			dest.set_element(i, j, left.get_element(i, j) * -1);
		}
	}
}

template<int W, int H>
void linear::abs(Matrix_T<W, H> const& left, Matrix_T<W, H>& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			float element = left.get_element(i, j);

			dest.set_element(i, j, element >= 0 ? element : element * -1);
		}
	}

}