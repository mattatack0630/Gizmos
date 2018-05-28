#include <string>
#include <fstream>
#include <Rendering/Display.h>
#include <Rendering/Shader.h>
#include <Rendering/Vao.h>
#include <Transforms/WorldTransform.h>
#include <Transforms/OrthoTransform.h>
#include <cmath>
#include <Transforms/PerspectiveTransform.h>
#include "Rendering/ModelLoader.h"
#include "Rendering/StaticMesh.h"
#include "../lib/glfw/deps/linmath.h"

std::string file_to_string(std::string name)
{
	std::ifstream infile{name};
	std::string file_contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
	return file_contents;
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// shader source code

int main()
{
	Display display = Display(640, 640, "Name");

	std::string vertex_source = file_to_string("/home/mathew/CLionProjects/Gizmos/tests/shader.vs");
	std::string fragment_source = file_to_string("/home/mathew/CLionProjects/Gizmos/tests/shader.fs");
	Shader shader = Shader(fragment_source, vertex_source);

	Vao vert_array = ModelLoader::load_OBJ("/home/mathew/CLionProjects/Gizmos/tests/test_file");

	WorldTransform view = WorldTransform(0, 0, 0, 0, 0, 0, 1, 1, 1);
	WorldTransform model = WorldTransform(0, 0, 0, 0, 0, 0, 1, 1, 1);
	//PerspectiveTransform projection = PerspectiveTransform(1, 0.1, 10000, M_PI / 3);
	OrthoTransform projection = OrthoTransform(-5, -5, 50, 5, 5, -50);
	Matrix4f MVP = Matrix4f();

	while (display.active()) {

		shader.bind();

		//view.set_rotation(0, map(sin(glfwGetTime()), -1, 1, -M_PI / 10, M_PI / 10), 0);

		float s = map(sin(glfwGetTime()), -1, 1, 5, 30);
		//model.set_scale(s,s,s);
		model.set_translation(0, 0, -s);
		model.set_rotation(glfwGetTime(), glfwGetTime(), glfwGetTime());

		MVP.set_identity();

		linear::dot(MVP, projection.get_matrix(), MVP);
		linear::dot(MVP, view.get_matrix(), MVP);
		linear::dot(MVP, model.get_matrix(), MVP);

		shader.upload_uniform_matrix4("MVP", MVP.get_pointer());

		vert_array.bind();

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glPointSize(10);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(vert_array.get_topology(), vert_array.get_vertex_count(), GL_UNSIGNED_INT, (void *) 0);

		display.update();
	}

	return 0;
}