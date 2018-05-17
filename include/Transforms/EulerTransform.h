//
// Created by mathew on 5/2/18.
//
#pragma once
#include "Transform.h"

class EulerTransform : public Transform
{

private:
	float rot_x;
	float rot_y;
	float rot_z;


protected:
	void calculate_matrix(SquareMatrix<4>& dest) override;

	void calculate_matrix_inverse(SquareMatrix<4>& dest) override;

public:
	EulerTransform(float x, float y, float z);
	void set_rotation(float x, float y, float z);
};
