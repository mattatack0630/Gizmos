cmake_minimum_required(VERSION 3.7)
project(Gizmos)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/main.cpp
        include/Linear_1/Matrix.h tests/OptimizedMatrixTest.cpp include/Linear_1/SquareMatrix.h src/Linear_1/Matrix2f.cpp
        include/Linear_1/Matrix2f.h src/Linear_1/Matrix3f.cpp include/Linear_1/Matrix3f.h src/Linear_1/Matrix4f.cpp
        include/Linear_1/Matrix4f.h include/Linear_1/Vector.h include/Linear_1/Vector2f.h src/Linear_1/Vector2f.cpp
        include/Linear_1/Vector3f.h src/Linear_1/Vector3f.cpp include/Linear_1/Vector4f.h src/Linear_1/Vector4f.cpp
        include/Transforms/Transform.h src/Transforms/Transform.cpp include/Transforms/TranslationTransform.h src/Transforms/TranslationTransform.cpp
        include/Transforms/EulerTransform.h src/Transforms/EulerTransform.cpp include/Transforms/ScaleTransform.h src/Transforms/ScaleTransform.cpp)
add_executable(Gizmos ${SOURCE_FILES})