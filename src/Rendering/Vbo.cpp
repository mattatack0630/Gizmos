//
// Created by mathew on 5/17/18.
//
#include <Rendering/Vbo.h>
#include <Rendering/GLErrorCall.h>

Vbo::Vbo(const void *data, GLuint chunk_size, GLuint chunk_amount, GLuint usage, GLuint buffer_type)
{

	this->chunk_size = chunk_size;
	this->chunk_amount = chunk_amount;
	this->buffer_type= buffer_type;

	GLCall(glGenBuffers(1, &vbo_id));
	GLCall(glBindBuffer(buffer_type, vbo_id));
	GLCall(glBufferData(buffer_type, (GLuint) (chunk_size * chunk_amount), data, usage));
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
	GLCall(glBindBuffer(buffer_type, vbo_id));
}

void Vbo::unbind()
{
 	//dunno
}

void Vbo::generate()
{
	// Unimplemented
}

void Vbo::destroy()
{
	GLCall(glDeleteBuffers(1, &vbo_id));
}
