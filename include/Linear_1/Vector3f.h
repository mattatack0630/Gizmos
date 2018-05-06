//
// Created by matthew on 8/9/17.
//

#pragma once


#include "Vector.h"

class Vector3f : public Vector<3>
{
public:
	Vector3f();
	Vector3f(float x, float y, float z);
};

namespace linear
{
	void cross(Vector3f const& left, Vector3f const& right, Vector3f& dest);
};


