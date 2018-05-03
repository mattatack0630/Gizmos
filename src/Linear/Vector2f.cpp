//
// Created by matthew on 8/9/17.
//

#include "Linear/Vector2f.h"


Vector2f::Vector2f() : Vector(2)
{

}

Vector2f::Vector2f(float x, float y) : Vector(2)
{
	this->set_element(0, x);
	this->set_element(1, y);
}
