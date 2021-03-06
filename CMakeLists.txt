cmake_minimum_required(VERSION 3.7)
project(Gizmos)

set(CMAKE_CXX_STANDARD 14)



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)
include_directories(lib/glad/include)
include_directories(lib/others/include)



include_directories(include)

set(SOURCE_FILES tests/TimeReporter.h tests/TimeReporter.cpp tests/MainTest.cpp include/Linear/Matrix.h include/Linear/Linear.h include/Linear/Vector.h include/Linear/SquareMatrix.h
            include/Transforms/Transform.h src/Transforms/Transform.cpp include/Transforms/TranslationTransform.h src/Transforms/TranslationTransform.cpp
            include/Transforms/ScaleTransform.h src/Transforms/ScaleTransform.cpp include/Transforms/EulerTransform.h src/Transforms/EulerTransform.cpp
            include/Transforms/WorldTransform.h src/Transforms/WorldTransform.cpp
        include/Transforms/OrthoTransform.h src/Transforms/OrthoTransform.cpp

            lib/glad/src/glad.c lib/glad/include/glad/glad.h lib/glad/include/KHR/khrplatform.h include/Rendering/Display.h src/Rendering/Display.cpp include/Rendering/Shader.h src/Rendering/Shader.cpp include/Rendering/Vao.h include/Rendering/Vbo.h src/Rendering/Vao.cpp src/Rendering/Vbo.cpp include/Rendering/ModelLoader.h lib/others/include/mem_usage.cpp src/Rendering/ModelLoader.cpp include/Rendering/StaticMesh.h include/Rendering/Vertex.h src/Rendering/StaticMesh.cpp include/Transforms/PerspectiveTransform.h src/Transforms/PerspectiveTransform.cpp include/Rendering/GLRenderer.h lib/others/stb_image.h include/Rendering/Texture2D.h src/Rendering/Texture2D.cpp include/Rendering/Fbo.h src/Rendering/Fbo.cpp include/Rendering/GLErrorCall.h lib/others/include/debug_break.h include/Rendering/RendererBase.h include/Rendering/Uniform.h include/Rendering/StaticRenderer.h src/Rendering/Uniform.cpp src/Rendering/StaticRenderer.cpp src/Rendering/RenderBase.cpp include/Rendering/Light.h)

add_executable(Gizmos ${SOURCE_FILES})




target_link_libraries(Gizmos glfw)
