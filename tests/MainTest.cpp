#include <string>
#include <fstream>
#include <Rendering/Shader.h>
#include "Rendering/ModelLoader.h"

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

int main()
{
	Matrix3f m1 = Matrix3f({5, 0, 0, 0, 5, 0, 0, 0, 5});
	Matrix3f m2 = Matrix3f({3, 0, 0, 0, 3, 0, 0, 0, 3});
	Matrix3f m3 = Matrix3f({1, 0, 0, 0, 1, 0, 1, 1, 1});
	Matrix3f m4 = Matrix3f({1, 0, 4, 4, 1, 0, 2, 0, 1});
	Matrix3f m5 = Matrix3f({1, 0, 0, 0, 1, 0, 0, 0, 1});

	m5 *= 5.0f * 2.0f;
	m5 += m2 + m3;
	m5 /= 14.0f;

	std::cout << m1 << std::endl;
}

/*
int main()
{
	Display display = Display(640, 640, "Name");

	Vao vert_array_0 = ModelLoader::load_OBJ("/home/mathew/CLionProjects/Gizmos/tests/test_file_1");
	Vao vert_array_1 = ModelLoader::load_OBJ("/home/mathew/CLionProjects/Gizmos/tests/test_file");
	//Vao vert_array_quad = ModelLoader::load_OBJ("/home/mathew/CLionProjects/Gizmos/tests/quad.obj");
	Texture2D texture1 = Texture2D("/home/mathew/CLionProjects/Gizmos/tests/wall.jpg");
	texture1.generate();

	StaticRenderer renderer = StaticRenderer();
	renderer.generate();

	Fbo screen = Fbo::screen_fbo();

	while (display.active()) {

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				Matrix4f MVP = Matrix4f();
				WorldTransform view = WorldTransform(0, 0, -100, 0, 0, 0, 1, 1, 1);
				WorldTransform model = WorldTransform(0, 0, 0, 0, 0, 0, 10, 10, 10);
				//OrthoTransform projection = OrthoTransform(-100, -100, 100, 100, 100, -100);
				PerspectiveTransform projection = PerspectiveTransform(1, 0.1, 600, M_PI / 3);

				model.set_translation(
						map(i, 0, 4, -50, 50),
						map(j, 0, 4, -50, 50),
						0
				);

				model.set_rotation(
						0,
						glfwGetTime(),
						0
				);

				MVP.set_identity();
				linear::dot(MVP, projection.get_matrix(), MVP);
				linear::dot(MVP, view.get_matrix(), MVP);
				linear::dot(MVP, model.get_matrix(), MVP);

				renderer.add_renderable(vert_array_1, {
						std::make_shared<Matrix4fUniform>("vMVP", MVP),
						std::make_shared<Matrix4fUniform>("vM", model.get_matrix()),
						std::make_shared<TextureUniform>("texture1", texture1.get_id(), 0)
				});

				renderer.add_point_light({
						Vector3f({1, 0, 1}),
						Vector3f({map(i, 0, 4, -50, 50), map(j, 0, 4, -50, 50), -40}),
						Vector3f({0.1, 0.014, 0.01})
				});
			}
		}

		renderer.pre_render();
		renderer.render(screen);
		renderer.post_render();

		display.update();
	}

	renderer.destroy();
	texture1.destroy();
	vert_array_0.destroy();
	vert_array_1.destroy();

	return 0;
}*/
