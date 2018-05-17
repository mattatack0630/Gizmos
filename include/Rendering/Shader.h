//
// Created by mathew on 5/17/18.
//

#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader
{
private:

	GLuint program_id = NULL_SHADER_ID;

	GLuint create_shader(GLuint type, std::string source);
	GLuint create_program(GLuint frag_id,GLuint  vert_id, GLuint geom_id);

public:
	static GLuint NULL_SHADER_ID;
	static GLuint BOUND_SHADER;

	Shader(std::string frag_shader, std::string vert_shader);
	Shader(std::string frag_shader, std::string vert_shader, std::string geom_shader);

	~Shader();

	void bind();
	GLuint get_id();

	// Change later
	std::unordered_map<std::string, GLint> uniform_locations;
	std::unordered_map<std::string, GLint> attrib_locations;
	GLint get_uniform_location(std::string uniform_name);
	GLint get_attrib_location(std::string uniform_name);
	void upload_uniform_matrix4(std::string uniform_name, const GLfloat *matrix);
};

/*
GLuint shader = glCreateShader(...);

// Get strings for glShaderSource.
glShaderSource(shader, ...);

glCompileShader(shader);

GLint isCompiled = 0;
glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
if(isCompiled == GL_FALSE)
{
GLint maxLength = 0;
glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

// The maxLength includes the NULL character
std::vector<GLchar> errorLog(maxLength);
glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

// Provide the infolog in whatever manor you deem best.
// Exit with failure.
glDeleteShader(shader); // Don't leak the shader.
return;
}

// Shader compilation is successful.

GLuint glCreateProgram();
The function takes no parameters.

After creating a program, the shader objects you wish to link to it must be attached to the program. This is done via this function:

void glAttachShader(GLuint program​, GLuint shader​);*/
