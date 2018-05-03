//
// Created by mathew on 5/2/18.
//
#pragma once

#include "Transform.h"
#include "EulerTransform.h"
#include "TranslationTransform.h"
#include "ScaleTransform.h"

class WorldTransform : public Transform
{
private:
	ScaleTransform scale;
	EulerTransform rotation;
	TranslationTransform translation;

protected:
	void calculate_matrix(Matrix4f& dest) override;

	void calculate_matrix_inverse(Matrix4f& dest) override;

public:
	WorldTransform();

	WorldTransform(float p_x, float p_y, float p_z,
				   float r_x, float r_y, float r_z,
				   float s_x, float s_y, float s_z);

	void set_scale(float x, float y, float z);

	void set_rotation(float x, float y, float z);

	void set_translation(float x, float y, float z);
};
