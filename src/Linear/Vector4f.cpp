//
// Created by matthew on 8/9/17.
//

#include "Linear/Vector4f.h"

Vector4f::Vector4f() : Vector(4)
{

}

Vector4f::Vector4f(float x, float y, float z, float w) : Vector(4)
{
	this->set_element(0, x);
	this->set_element(1, y);
	this->set_element(2, z);
	this->set_element(3, w);
}

