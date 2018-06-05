//
// Created by mathew on 5/29/18.
//

#pragma once

#include <string>
#include <iostream>
#include "../../lib/glfw/deps/glad/glad.h"

class Texture2D{
private:
	int width;
	int height;
	int channels;

	GLuint texture_id;
	GLuint bind_location;

	unsigned char *data;

public:
	Texture2D(GLuint id, int w, int h);
	Texture2D(int w, int h);
	Texture2D(std::string location);

	void destroy();
	void generate();

	void bind(GLuint spot);
	void unbind();
	void generate_texture(unsigned char* data);
	void applyParameteri(GLuint name, GLuint value);
	GLuint get_bind_location();

	GLuint get_id();
};
