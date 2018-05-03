//
// Created by mathew on 5/2/18.
//
#pragma once

#include "../Linear/Matrix4f.h"
#include "Transform.h"

class ScaleTransform : public Transform
{
private:
	float scale_x;
	float scale_y;
	float scale_z;

protected:
	void calculate_matrix(Matrix4f& dest) override;

	void calculate_matrix_inverse(Matrix4f& dest) override;

public:
	ScaleTransform(float x, float y, float z);
	void set_scale(float x, float y, float z);
};