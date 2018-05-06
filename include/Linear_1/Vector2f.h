//
// Created by matthew on 8/9/17.
//

#pragma once

#include "Vector.h"

class Vector2f : public Vector<2>
{
public:
	Vector2f();
	Vector2f(float x, float y);
};
//template<int N>
//float angle(Vector<N> const& left, Vector<N> const& right); // Maybe remove, this has no meaning for most vectors

