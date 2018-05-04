//
// Created by matthew on 8/7/17.
//

#include "Linear/Matrix.h"

#include <iomanip>
#include <cmath>

Matrix::Matrix(int w, int h)
{
	m_width = w;
	m_height = h;

	// Init element array

	m_elementArray.reserve(w);

	for (int i = 0; i < m_height; i++) {
		std::vector<float> row_list;
		row_list.reserve(h);

		m_elementArray.push_back(row_list);

		for (int j = 0; j < m_width; j++) {
			m_elementArray[i].emplace_back(0.0f);
		}
	}
}

Matrix::Matrix(const Matrix& src)
{
	m_width = src.m_width;
	m_height = src.m_height;

	for (int i = 0; i < m_height; i++) {
		std::vector<float> row_list;
		m_elementArray.push_back(row_list);

		for (int j = 0; j < m_width; j++) {
			m_elementArray[i].push_back(src.get_element(j, i));
		}
	}
}

void Matrix::set_zero()
{
	for (int i = 0; i < m_width; i++) {
		for (int j = 0; j < m_height; j++) {
			set_element(i, j, 0);
		}
	}
}

// Operators Overloading

std::ostream& operator<<(std::ostream& os, Matrix const& matrix)
{
	os.precision(3);

	for (int j = 0; j < matrix.m_height; j++) {
		os << "[";

		for (int i = 0; i < matrix.m_width; i++) {
			if (i != matrix.m_width - 1)
				os << std::left << std::setw(10);
			os << std::fixed << matrix.get_element(i, j);
		}

		os << "]";
		os << std::endl;
	}

	return os;
}

bool operator==(Matrix const& left, Matrix const& right)
{
	return Matrix::are_equal(left, right);
}

bool operator!=(Matrix const& left, Matrix const& right)
{
	return !Matrix::are_equal(left, right);
}

Matrix operator+(Matrix const& left, Matrix const& right)
{
	Matrix dest(right.m_width, right.m_height);

	Matrix::add(left, right, dest);

	return dest;
}

Matrix operator-(Matrix const& left, Matrix const& right)
{
	Matrix dest(right.m_width, right.m_height);

	Matrix::sub(left, right, dest);

	return dest;
}

Matrix operator*(Matrix const& left, Matrix const& right)
{
	Matrix dest(right.m_width, left.m_height);

	Matrix::dot(left, right, dest);

	return dest;
}


void Matrix::copy(Matrix const& left, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j));
		}
	}
}

bool Matrix::are_equal(Matrix const& left, Matrix const& right, float tolerance)
{
	bool equal = left.m_height == right.m_height && left.m_width == right.m_width;

	for (int i = 0; i < left.m_width && equal; i++) {
		for (int j = 0; j < left.m_height && equal; j++) {
			float diff = fabsf(left.get_element(i, j) - right.get_element(i, j));
			equal &= (diff <= tolerance);
		}
	}

	return equal;
}

// Matrix Algebra

void Matrix::add(Matrix const& left, Matrix const& right, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) + right.get_element(i, j));
		}
	}
}

void Matrix::sub(Matrix const& left, Matrix const& right, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) - right.get_element(i, j));
		}
	}

}

void Matrix::component_mult(Matrix const& left, Matrix const& right, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) * right.get_element(i, j));
		}
	}

}

void Matrix::component_div(Matrix const& left, Matrix const& right, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error
	//Div By zero error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) / right.get_element(i, j));
		}
	}

}

void Matrix::dot(Matrix const& left, Matrix const& right, Matrix& dest)
{
	// check dest size error (must == left.height right.width)
	// check left.size = right.size error

	float t_elements[right.m_width][left.m_height];

	for (int i = 0; i < left.m_height; i++) {
		for (int j = 0; j < right.m_width; j++) {
			float elementVal = 0;

			for (int k = 0; k < left.m_width; k++) {
				elementVal += (left.get_element(k, i) * right.get_element(j, k));
			}

			t_elements[j][i] = elementVal;
		}
	}

	//dest.setElements(t_elements); // use later
	for (int i = 0; i < dest.m_width; i++) {
		for (int j = 0; j < dest.m_height; j++) {
			dest.set_element(i, j, t_elements[i][j]);
		}
	}

}

void Matrix::scale(Matrix const& left, float scale, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) * scale);
		}
	}

}

void Matrix::transpose(Matrix const& left, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	float t_elements[left.m_height][left.m_width];

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			t_elements[j][i] = left.get_element(i, j);
		}
	}

	//dest.setElements(t_elements); // use later
	for (int i = 0; i < dest.m_width; i++) {
		for (int j = 0; j < dest.m_height; j++) {
			dest.set_element(i, j, t_elements[i][j]);
		}
	}

}

void Matrix::negate(Matrix const& left, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, left.get_element(i, j) * -1.0f);
		}
	}

}

void Matrix::abs(Matrix const& left, Matrix& dest)
{
	// check dest size error
	// check left.size = right.size error

	for (int i = 0; i < left.m_width; i++) {
		for (int j = 0; j < left.m_height; j++) {
			dest.set_element(i, j, fabsf(left.get_element(i, j)));
		}
	}

}



