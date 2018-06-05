//
// Created by mathew on 6/2/18.
//

#pragma once

#include <string>
#include <Linear/SquareMatrix.h>
#include "../../lib/glfw/deps/glad/glad.h"
#include "GLErrorCall.h"
#include "Vertex.h"

class Uniform
{
protected:
	std::string name;

public:
	Uniform(const std::string& name) : name(name) {}

	std::string get_name() { return name; };

	virtual void upload_to_location(GLint shader_loc) = 0;
};

class IntUniform : public Uniform
{
protected:
	int value = 0;

public:
	IntUniform(const std::string& name, int value) : Uniform(name), value(value) {}

	void set_value(int value);

	void upload_to_location(GLint shader_loc);
};

class FloatUniform : public Uniform
{
protected:
	float value = 0;

public:
	FloatUniform(const std::string& name, float value) : Uniform(name), value(value) {}

	void set_value(float value);

	void upload_to_location(GLint shader_loc);
};

class Vector3fUniform : public Uniform
{
protected:
	Vector3f value;

public:
	Vector3fUniform(const std::string& name,  Vector3f value) : Uniform(name), value(value) {}

	void set_value(Vector3f value);

	void upload_to_location(GLint shader_loc);
};

class Matrix4fUniform : public Uniform
{
protected:
	Matrix4f value;

public:
	Matrix4fUniform(const std::string& name,  Matrix4f value) : Uniform(name), value(value) {}

	void set_value(Matrix4f value);

	void upload_to_location(GLint shader_loc);
};

class TextureUniform : public Uniform
{
protected:
	GLuint tex_id = 0;
	GLuint tex_loc = 0;

public:
	TextureUniform(const std::string& name, GLuint tex_id, GLuint tex_loc) : Uniform(name), tex_id(tex_id), tex_loc(tex_loc) {}

	void set_value(GLuint tex_id, GLuint tex_loc);

	void upload_to_location(GLint shader_loc);
};