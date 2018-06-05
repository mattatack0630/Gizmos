//
// Created by mathew on 6/2/18.
//


#include <Rendering/Uniform.h>

void IntUniform::set_value(int value)
{
	this->value = value;
}

void IntUniform::upload_to_location(GLint shader_loc)
{
	GLCall(glUniform1i(shader_loc, value));
}


void FloatUniform::set_value(float value)
{
	this->value = value;
}

void FloatUniform::upload_to_location(GLint shader_loc)
{
	GLCall(glUniform1f(shader_loc, value));
}


void Matrix4fUniform::set_value(Matrix4f value)
{
	this->value = value;
}

void Matrix4fUniform::upload_to_location(GLint shader_loc)
{
	GLCall(glUniformMatrix4fv(shader_loc, 1, GL_FALSE, value.get_pointer()));
}

void TextureUniform::set_value(GLuint tex_id, GLuint tex_loc)
{
	this->tex_id = tex_id;
	this->tex_loc = tex_loc;
}

void TextureUniform::upload_to_location(GLint shader_loc)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + tex_loc));
	GLCall(glBindTexture(GL_TEXTURE_2D, tex_id));
	GLCall(glUniform1i(shader_loc, tex_loc)); // set it manually
}

void Vector3fUniform::set_value(Vector3f value)
{
	this->value = value;
}

void Vector3fUniform::upload_to_location(GLint shader_loc)
{
	GLCall(glUniform3fv(shader_loc, 1, value.get_pointer()));
}
