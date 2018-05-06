//
// Created by mathew on 5/4/18.
//

#include <Linear_1/Matrix.h>
#include <iostream>
#include <Linear_1/SquareMatrix.h>
#include <Linear_1/Matrix2f.h>
#include <Linear_1/Matrix4f.h>
#include <Linear_1/Matrix3f.h>
#include <Linear_1/Vector2f.h>
#include <Linear_1/Vector3f.h>
#include <Transforms/TranslationTransform.h>
#include <Linear_1/Vector4f.h>

int main()
{

	Vector4f v1 = Vector4f(2,8,1,1);

	TranslationTransform transform = TranslationTransform(10,10,10);

	std::cout<<v1<<std::endl;
	std::cout<<transform.get_matrix()<<std::endl;
	std::cout<<transform.get_matrix() * v1<<std::endl;

	return 0;

}
