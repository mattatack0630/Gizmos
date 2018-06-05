//
// Created by mathew on 5/17/18.
//

#include <Rendering/Shader.h>
#include <vector>
#include <Rendering/GLErrorCall.h>

GLuint Shader::NULL_SHADER_ID = 12345;
GLuint Shader::BOUND_SHADER = NULL_SHADER_ID;

Shader::Shader(std::string frag_shader, std::string vert_shader) :
		program_id(NULL_SHADER_ID),
		frag_source(frag_shader),
		vert_source(vert_shader),
		geom_source("")
{
}

Shader::Shader(std::string frag_shader, std::string vert_shader, std::string geom_shader) :
		program_id(NULL_SHADER_ID),
		frag_source(frag_shader),
		vert_source(vert_shader),
		geom_source(geom_shader)
{
}

void Shader::generate()
{
	GLuint frag_id = frag_source.empty() ? NULL_SHADER_ID : create_shader(GL_FRAGMENT_SHADER, frag_source);
	GLuint vert_id = vert_source.empty() ? NULL_SHADER_ID : create_shader(GL_VERTEX_SHADER, vert_source);
	GLuint geom_id = geom_source.empty() ? NULL_SHADER_ID : create_shader(GL_GEOMETRY_SHADER, geom_source);
	program_id = create_program(frag_id, vert_id, geom_id);
}

void Shader::destroy()
{
	if (program_id != NULL_SHADER_ID) {
		GLCall(glDeleteProgram(program_id));
	}
}

void Shader::bind()
{
	//if (BOUND_SHADER != program_id) {
	GLCall(glUseProgram(program_id));
	//}
}

GLuint Shader::get_id()
{
	return program_id;
}

GLuint Shader::create_shader(GLuint type, std::string source)
{
	GLuint shader_id = glCreateShader(type);
	const GLchar *source_chars = source.c_str();

	// Get strings for glShaderSource.
	GLCall(glShaderSource(shader_id, 1, &source_chars, NULL));

	GLCall(glCompileShader(shader_id));

	GLint isCompiled = 0;
	GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled));

	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		GLCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		GLCall(glGetShaderInfoLog(shader_id, maxLength, &maxLength, &errorLog[0]));
		// Provide the infolog in whatever manor you deem best.

		for (GLchar c : errorLog)
			std::cout << c;
		std::cout << std::endl;

		// Exit with failure.
		GLCall(glDeleteShader(shader_id)); // Don't leak the shader.

		return NULL_SHADER_ID;
	}

	return shader_id;
}

GLuint Shader::create_program(GLuint frag_id, GLuint vert_id, GLuint geom_id)
{
	GLuint program_id = glCreateProgram();
	if (frag_id != NULL_SHADER_ID) { GLCall(glAttachShader(program_id, frag_id);) }
	if (vert_id != NULL_SHADER_ID) { GLCall(glAttachShader(program_id, vert_id);) } // ERROR CATCHING
	if (geom_id != NULL_SHADER_ID) { GLCall(glAttachShader(program_id, geom_id);) }

	GLCall(glLinkProgram(program_id));

	// print linking errors if any
	GLint success = 0;
	GLCall(glGetProgramiv(program_id, GL_LINK_STATUS, &success));

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		GLCall(glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength));

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		GLCall(glGetProgramInfoLog(program_id, maxLength, &maxLength, &errorLog[0]));
		// Provide the infolog in whatever manor you deem best.

		// Exit with failure.
		GLCall(glDeleteProgram(program_id)); // Don't leak the shader.

		return NULL_SHADER_ID;
	}

	// delete the shaders as they're linked into our program now and no longer necessery

	if (frag_id != NULL_SHADER_ID) {
		GLCall(glDeleteShader(frag_id));
	}
	if (vert_id != NULL_SHADER_ID) {
		GLCall(glDeleteShader(vert_id));
	}
	if (geom_id != NULL_SHADER_ID) {
		GLCall(glDeleteShader(geom_id));
	}

	return program_id;
}

// These are here for right now, may change to diff system later

GLint Shader::get_uniform_location(std::string uniform_name)
{
	if (uniform_locations.find(uniform_name) != uniform_locations.end()) {
		return uniform_locations[uniform_name];
	} else {
		GLCall(GLint new_location = glGetUniformLocation(program_id, uniform_name.c_str()));
		uniform_locations[uniform_name] = new_location;
		return new_location;
	}
}

void Shader::upload_uniforms(std::vector<std::shared_ptr<Uniform>> uniforms)
{
	for (auto uniform : uniforms) {
		GLint loc = get_uniform_location(uniform->get_name());
		uniform->upload_to_location(loc);
	}
}

void Shader::upload_uniform(std::shared_ptr<Uniform> uniform)
{
	GLint loc = get_uniform_location(uniform->get_name());
	uniform->upload_to_location(loc);
}

