//
// Created by matthew on 8/9/17.
//

#include "Linear_1/Vector3f.h"

Vector3f::Vector3f()
{

}

Vector3f::Vector3f(float x, float y, float z)
{
	this->set_element(0, x);
	this->set_element(1, y);
	this->set_element(2, z);
}


void linear::cross(Vector3f const& left, Vector3f const& right, Vector3f& dest)
{
	float l_x = left.get_element(0);
	float l_y = left.get_element(1);
	float l_z = left.get_element(2);
	float r_x = right.get_element(0);
	float r_y = right.get_element(1);
	float r_z = right.get_element(2);

	dest.set_element(0, (l_y * r_z) - (l_z * r_y));
	dest.set_element(0, (l_z * r_x) - (l_x * r_z));
	dest.set_element(0, (l_x * r_y) - (l_y * r_x));
}
