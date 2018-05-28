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
	GLint get_uniform_location(std::string uniform_name);
	void upload_uniform_matrix4(std::string uniform_name, const GLfloat *matrix);
};
