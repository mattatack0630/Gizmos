//
// Created by mathew on 5/17/18.
//

#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Texture2D.h"
#include "Uniform.h"

class Shader
{
private:
	std::unordered_map<std::string, GLint> uniform_locations;

	GLuint program_id = NULL_SHADER_ID;
	std::string frag_source;
	std::string geom_source;
	std::string vert_source;

	GLuint create_shader(GLuint type, std::string source);

	GLuint create_program(GLuint frag_id, GLuint vert_id, GLuint geom_id);

public:
	static GLuint NULL_SHADER_ID;
	static GLuint BOUND_SHADER;

	Shader(std::string frag_shader, std::string vert_shader, std::string geom_shader);

	Shader(std::string frag_shader, std::string vert_shader);

	GLuint get_id();

	void generate();

	void destroy();

	void bind();

	GLint get_uniform_location(std::string uniform_name);

	void upload_uniforms(std::vector<std::shared_ptr<Uniform>> uniforms);

	void upload_uniform(std::shared_ptr<Uniform> uniform);

	template<typename T, typename... Args>
	void upload_uniform(Args&&... args)
	{
		T uniform = T(std::forward<Args>(args)...);

		GLint loc = get_uniform_location(uniform.get_name());
		uniform.upload_to_location(loc);
	}
};
