//
// Created by mathew on 5/17/18.
//

#pragma once

#include <vector>
#include <glad/glad.h>

struct AttribData{
	GLuint index, components, type, offset;
};

class Vbo
{
public:
	GLuint buffer_type;
	GLuint vbo_id;
	GLuint chunk_size;
	GLuint chunk_amount;

	std::vector<AttribData> attribs;

	Vbo(const void* data, GLuint chunk_size, GLuint chunk_amount);
	Vbo(const void* data, GLuint chunk_size, GLuint chunk_amount, GLuint usage);
	Vbo(const void *data, GLuint chunk_size, GLuint chunk_amount, GLuint usage, GLuint buffer_type);

	void set_attrib_pointer(GLuint index, GLuint components, GLuint type, GLuint offset);
	void bind();
	void unbind();
};

