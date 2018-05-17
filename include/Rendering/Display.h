//
// Created by mathew on 5/17/18.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display{
public:
	GLFWwindow *window;
	Display(int w, int h, const char* name);
	~Display();
	void update();
	bool active();
};