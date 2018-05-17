//
// Created by mathew on 5/4/18.
//

#pragma once

#include <array>
#include <iomanip>
#include <iostream>

template<int W, int H, typename T = float>
class Matrix
{
protected:
	// Stored [column][row] or [x][y] or y*width+x
	std::array<T, W * H> elements = {};

public:
	Matrix();

	Matrix(std::array<T, W * H> src);

	Matrix(const Matrix<W, H, T>& src);

	inline void set_elements(std::array<T, W * H> src) { std::copy(std::begin(src), std::end(src), std::begin(elements)); }

	inline void set_element(int x, int y, T value) { elements[y * W + x] = value; }

	inline T get_element(int x, int y) const { return elements[y * W + x]; }

	inline const std::array<T, W * H> get_array() { return elements; }

	inline const T* get_pointer() { return elements.data(); }

	inline int get_height() const { return H; }

	inline int get_width() const { return W; }

	void set_zero();

	bool is_equal(Matrix<W, H, T> matrix, float tolerance = 0.0f) const;
};

template<int W, int H, typename T>
Matrix<W, H, T>::Matrix() :
		elements({})
{
}

template<int W, int H, typename T>
Matrix<W, H, T>::Matrix(std::array<T, W * H> src):
		elements(src)
{
}

template<int W, int H, typename T>
Matrix<W, H, T>::Matrix(const Matrix<W, H, T>& src) :
		elements(src.elements)
{
}

template<int W, int H, typename T>
bool Matrix<W, H, T>::is_equal(Matrix<W, H, T> matrix, float tolerance) const
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

template<int W, int H, typename T>
void Matrix<W, H, T>::set_zero()
{
	for (int x = 0; x < W; x++) {
		for (int y = 0; y < H; y++) {
			set_element(x, y, 0);
		}
	}
}

template<int W, int H, typename T>
std::ostream& operator<<(std::ostream& os, Matrix<W, H, T> const& matrix)
{
	os.precision(3);

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

template<int W, int H, typename T>
bool operator==(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right)
{
	return left.is_equal(right);
}

template<int W, int H, typename T>
bool operator!=(Matrix<W, H, T> const& left, Matrix<W, H, T> const& right)
{
	return !left.is_equal(right);
}