//
// Created by mathew on 5/6/18.
//

#include "Linear_1/Matrix3f.h"

Matrix3f::Matrix3f()
{

}

float Matrix3f::determinate()
{
	return linear::determinate_3x3(*this);
}

float linear::determinate_3x3(Matrix3f const& left)
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
	float result = (a * e * i) + (b * f * g) + (c * d * h) - (g * e * c) - (h * f * a) - (i * d * b);
	return result;
}

void linear::invert_3x3(Matrix3f const& left, Matrix3f& dest)
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
	}

}