//
// Created by mathew on 5/2/18.
//

#pragma once

#include "Transform.h"

class TranslationTransform : public Transform
{
private:
	float position_x;
	float position_y;
	float position_z;


protected:
	void calculate_matrix(SquareMatrix<4>& dest) override;

	void calculate_matrix_inverse(SquareMatrix<4>& dest) override;

public:
	TranslationTransform(float x, float y, float z);
	void set_translation(float x, float y, float z);
};