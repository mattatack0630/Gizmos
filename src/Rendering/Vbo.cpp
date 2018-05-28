//
// Created by mathew on 5/17/18.
//
#include <Rendering/Vbo.h>

Vbo::Vbo(const void *data, GLuint chunk_size, GLuint chunk_amount, GLuint usage, GLuint buffer_type)
{
	glGenBuffers(1, &vbo_id);
	glBindBuffer(buffer_type, vbo_id);

	this->chunk_size = chunk_size;
	this->chunk_amount = chunk_amount;
	this->buffer_type= buffer_type;

	// fill with data
	glBufferData(buffer_type, (GLuint) (chunk_size * chunk_amount), data, usage);
}

Vbo::Vbo(const void *data, GLuint chunk_size, GLuint chunk_amount, GLuint usage) :
	Vbo(data, chunk_size, chunk_amount, usage, GL_ARRAY_BUFFER)
{
}

Vbo::Vbo(const void *data, GLuint chunk_size, GLuint chunk_amount) :
		Vbo(data, chunk_size, chunk_amount, GL_STATIC_DRAW, GL_ARRAY_BUFFER)
{
}

void Vbo::set_attrib_pointer(GLuint index, GLuint components, GLuint type, GLuint offset)
{
	attribs.push_back({index, components, type, offset});
}

void Vbo::bind()
{
	glBindBuffer(buffer_type, vbo_id);
}

void Vbo::unbind()
{
 	//dunno
}
