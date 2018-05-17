//
// Created by mathew on 5/4/18.
//
/*
#include <Transforms/Transform.h>
#include <Transforms/WorldTransform.h>
#include <Rendering/Display.h>
#include <string>
#include <Rendering/Shader.h>
#include "../lib/glfw/deps/linmath.h"

static const struct
{
	float x, y;
	float r, g, b;
} vertices[3] =
		{
				{-0.6f, -0.4f, 1.f, 0.f, 0.f},
				{0.6f,  -0.4f, 0.f, 1.f, 0.f},
				{0.f,   0.6f,  0.f, 0.f, 1.f}
		};

int main(void)
{
	Display display = Display(400, 400, "Name");

	std::string frag = "varying vec3 color;\n"
					   "void main()\n"
					   "{\n"
					   "    gl_FragColor = vec4(color, 1.0);\n"
					   "}\n";

	std::string vert = "uniform mat4 MVP;\n"
					   "attribute vec3 vCol;\n"
					   "attribute vec2 vPos;\n"
					   "varying vec3 color;\n"
					   "void main()\n"
					   "{\n"
					   "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
					   "    color = vCol;\n"
					   "}\n";

	Shader shader = Shader(frag, vert);

	GLuint vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLint mvp_location = glGetUniformLocation(shader.get_id(), "MVP");
	GLint vpos_location = glGetAttribLocation(shader.get_id(), "vPos");
	GLint vcol_location = glGetAttribLocation(shader.get_id(), "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) 0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) (sizeof(float) * 2));

	while (display.active()) {

		glViewport(0, 0, 400, 400);
		glClear(GL_COLOR_BUFFER_BIT);
		mat4x4 m, p, mvp;

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		mat4x4_ortho(p, -400 / (float) 400, 400 / (float) 400, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		const GLfloat matrix[16] =
				{
						1, 0, 0, 0,
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1
				};

		shader.bind();
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		display.update();
	}


	return 0;
}*/


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <stdlib.h>
#include <stdio.h>
#include <Rendering/Display.h>
#include <string>
#include <Rendering/Shader.h>
#include <Linear/Matrix.h>
#include <Linear/Linear.h>
#include <Transforms/Transform.h>
#include <Transforms/WorldTransform.h>
#include <Transforms/OrthoTransform.h>
#include <unordered_map>
#include "../lib/glfw/deps/linmath.h"

static const struct
{
	float x, y;
	float r, g, b;
} vertices[3] =
		{
				{-0.6f, -0.4f, 1.f, 0.f, 0.f},
				{0.6f,  -0.4f, 0.f, 1.f, 0.f},
				{0.f,   0.6f,  0.f, 0.f, 1.f}
		};

std::string vertex_shader_text =
		"uniform mat4 MVP;\n"
		"attribute vec3 vCol;\n"
		"attribute vec2 vPos;\n"
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
		"    color = vCol;\n"
		"}\n";

std::string fragment_shader_text =
		"varying vec3 color;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = vec4(color, 1.0);\n"
		"}\n";


int main(void)
{

	Display display(400, 400, "TEST");
	GLuint vertex_buffer;
	GLint vpos_location, vcol_location;

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader shader = Shader(fragment_shader_text, vertex_shader_text);

	vpos_location = shader.get_attrib_location( "vPos");
	vcol_location = shader.get_attrib_location( "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) 0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *) (sizeof(float) * 2));

	while (display.active()) {

		GLfloat ratio = 400 / (GLfloat) 400;
		Matrix<4, 4, GLfloat> mvp = Matrix<4, 4, GLfloat>();
		OrthoTransform ortho = OrthoTransform(-ratio, -1, 1, ratio, 1, -1);
		WorldTransform world = WorldTransform(0, 0, 0, 0, 0, (GLfloat) glfwGetTime(), 1, 1, 1);
		linear::dot(ortho.get_matrix(), world.get_matrix(), mvp);
		shader.upload_uniform_matrix4("MVP", mvp.get_pointer());

		shader.bind();

		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		display.update();
	}

	return 0;
}