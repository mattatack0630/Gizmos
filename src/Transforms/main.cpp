#include <tgmath.h>
#include <cmath>
#include <Transforms/WorldTransform.h>
#include <Linear/Vector4f.h>

//
// Created by mathew on 5/2/18.
//
/*
int main()
{
	Transform *transform1 = new ScaleTransform(3, 3, 3);
	Transform *transform2 = new EulerTransform(0, 0, M_PI / 2.0f);
	Transform *transform3 = new TranslationTransform(1, 1, 1);

	Transform *transform4 = new WorldTransform(1, 1, 1,
											   0, 0, M_PI / 2.0f,
											   3, 3, 3);

	Vector4f point1 = Vector4f(1, 0, 0, 1);
	Vector4f point2 = Vector4f(1, 0, 0, 1);

	Matrix::dot(transform1->get_matrix(), point1, point1);
	Matrix::dot(transform2->get_matrix(), point1, point1);
	Matrix::dot(transform3->get_matrix(), point1, point1);
*/
/*
	Matrix::dot(transform3->get_matrix_inverse(), point, point);
	Matrix::dot(transform2->get_matrix_inverse(), point, point);
	Matrix::dot(transform1->get_matrix_inverse(), point, point);
*//*
	Matrix::dot(transform4->get_matrix(), point2, point2);
	//Matrix::dot(transform4->get_matrix_inverse(), point2, point2);

	std::cout << (transform3->get_matrix()*transform2->get_matrix()*transform1->get_matrix()) << std::endl;
	std::cout << point1 << std::endl;
	std::cout << point2 << std::endl;
	std::cout << transform1->get_matrix() << std::endl;
	std::cout << transform2->get_matrix() << std::endl;
	std::cout << transform3->get_matrix() << std::endl;
	std::cout << transform4->get_matrix() << std::endl;

	delete (transform1);
	delete (transform2);
	delete (transform3);
	delete (transform4);

	return 0;
}
*/