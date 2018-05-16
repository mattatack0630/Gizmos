//
// Created by mathew on 5/4/18.
//


#include "Matrix.h"
#include "Vector.h"
#include "SquareMatrix.h"
#include "Linear.h"

int main()
{
	SquareMatrix_T<4, float> square1 = SquareMatrix_T<4, float>();
	SquareMatrix_T<4, float> square2 = SquareMatrix_T<4, float>();
	square1.set_elements({1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 3, 5, 6, 9});

	Vector_T<2> v1 = Vector_T<2>({1,3});
	Vector_T<2> v2 = Vector_T<2>(v1);

	linear::adjoint_invert(square1, square2);

	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << square1 << std::endl;
	std::cout << square2 << std::endl;
	std::cout << linear::determinate(square1) << std::endl;

	return 0;
}
/*
 * tests/OptimizedMatrixTest.cpp include/Linear_1/SquareMatrix.h src/Linear_1/Matrix2f.cpp
        include/Linear_1/Matrix2f.h src/Linear_1/Matrix3f.cpp include/Linear_1/Matrix3f.h src/Linear_1/Matrix4f.cpp
        include/Linear_1/Matrix4f.h include/Linear_1/Vector.h include/Linear_1/Vector2f.h src/Linear_1/Vector2f.cpp
        include/Linear_1/Vector3f.h src/Linear_1/Vector3f.cpp include/Linear_1/Vector4f.h src/Linear_1/Vector4f.cpp
        include/Transforms/Transform.h src/Transforms/Transform.cpp include/Transforms/TranslationTransform.h src/Transforms/TranslationTransform.cpp
        include/Transforms/EulerTransform.h src/Transforms/EulerTransform.cpp include/Transforms/ScaleTransform.h src/Transforms/ScaleTransform.cpp
        include/Transforms/WorldTransform.h src/Transforms/WorldTransform.cpp include/Transforms/OrthographicTransform.cpp include/Transforms/OrthographicTransform.h include/Transforms/AABB.h
        tests/TimeReporter.cpp tests/TimeReporter.h*/