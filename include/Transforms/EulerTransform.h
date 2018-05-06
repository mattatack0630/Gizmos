//
// Created by mathew on 5/2/18.
//

#include "Transform.h"

class EulerTransform : public Transform
{

private:
	float rot_x;
	float rot_y;
	float rot_z;


protected:
	void calculate_matrix(Matrix4f& dest) override;

	void calculate_matrix_inverse(Matrix4f& dest) override;

public:
	EulerTransform(float x, float y, float z);
	void set_rotation(float x, float y, float z);
};
