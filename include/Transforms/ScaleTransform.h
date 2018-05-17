//
// Created by mathew on 5/2/18.
//
#pragma once

#include "Transform.h"

class ScaleTransform : public Transform
{
private:
	float scale_x;
	float scale_y;
	float scale_z;

protected:
	void calculate_matrix(SquareMatrix<4>& dest) override;

	void calculate_matrix_inverse(SquareMatrix<4>& dest) override;

public:
	ScaleTransform(float x, float y, float z);
	void set_scale(float x, float y, float z);
};