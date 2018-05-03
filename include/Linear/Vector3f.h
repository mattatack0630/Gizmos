//
// Created by matthew on 8/9/17.
//

#pragma once


#include "Vector.h"

class Vector3f : public Vector
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);

	void cross(Vector3f const &left, Vector3f const &right, Vector3f &dest);
};



