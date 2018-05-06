//
// Created by mathew on 5/6/18.
//

#include "Linear_1/Matrix2f.h"

Matrix2f::Matrix2f(){

}


float Matrix2f::determinate()
{
	return linear::determinate_2x2(*this);
}

float linear::determinate_2x2(Matrix2f const& left)
{
	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(0, 1);
	float d = left.get_element(1, 1);
	float result = a * d - c * b;
	return result;
}

void linear::invert_2x2(Matrix2f const& left, Matrix2f& dest)
{

	float a = left.get_element(0, 0);
	float b = left.get_element(1, 0);
	float c = left.get_element(0, 1);
	float d = left.get_element(1, 1);
	float det = a * d - c * b;

	// throw div by zero exe

	if (det != 0) {
		dest.set_element(0, 0, d / det);
		dest.set_element(1, 0, -b / det);
		dest.set_element(0, 1, -c / det);
		dest.set_element(1, 1, a / det);
	}
}
