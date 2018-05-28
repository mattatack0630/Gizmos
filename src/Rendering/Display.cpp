//
// Created by mathew on 5/17/18.
//

#include <Rendering/Display.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

static void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Display::Display(int w, int h, const char *name)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(w, h, name, NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval(1);
}

void Display::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Display::active()
{
	return !glfwWindowShouldClose(window);
}

Display::~Display()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

