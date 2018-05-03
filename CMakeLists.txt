cmake_minimum_required(VERSION 3.7)
project(Gizmos)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/main.cpp src/Linear/Matrix.cpp include/Linear/Matrix.h src/Linear/Vector.cpp include/Linear/Vector.h src/Linear/SquareMatrix.cpp include/Linear/SquareMatrix.h src/Linear/Vector2f.cpp include/Linear/Vector2f.h src/Linear/Vector3f.cpp include/Linear/Vector3f.h src/Linear/Vector4f.cpp include/Linear/Vector4f.h src/Linear/Matrix3f.cpp include/Linear/Matrix3f.h src/Linear/Matrix2f.cpp include/Linear/Matrix2f.h src/Linear/Matrix4f.cpp include/Linear/Matrix4f.h src/Transforms/Transform.cpp include/Transforms/Transform.h src/Transforms/TranslationTransform.cpp include/Transforms/TranslationTransform.h src/Transforms/main.cpp src/Transforms/ScaleTransform.cpp include/Transforms/ScaleTransform.h include/Transforms/EulerTransform.cpp include/Transforms/EulerTransform.h src/Transforms/WorldTransform.cpp include/Transforms/WorldTransform.h tests/MatrixRowTest.cpp)
add_executable(Gizmos ${SOURCE_FILES})