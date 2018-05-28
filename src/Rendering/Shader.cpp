//
// Created by mathew on 5/17/18.
//

#include <Rendering/Shader.h>
#include <vector>

GLuint Shader::NULL_SHADER_ID = 12345;
GLuint Shader::BOUND_SHADER = NULL_SHADER_ID;

Shader::Shader(std::string frag_shader, std::string vert_shader)
{
	GLuint frag_id = create_shader(GL_FRAGMENT_SHADER, frag_shader);
	GLuint vert_id = create_shader(GL_VERTEX_SHADER, vert_shader);
	this->program_id = create_program(frag_id, vert_id, NULL_SHADER_ID);
}

Shader::Shader(std::string frag_shader, std::string vert_shader, std::string geom_shader)
{
	GLuint frag_id = create_shader(GL_FRAGMENT_SHADER, frag_shader);
	GLuint vert_id = create_shader(GL_VERTEX_SHADER, vert_shader);
	GLuint geom_id = create_shader(GL_GEOMETRY_SHADER, geom_shader);
	this->program_id = create_program(frag_id, vert_id, geom_id);
}

void Shader::bind()
{
	if (BOUND_SHADER != program_id) {
		glUseProgram(program_id);
	}
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
	glShaderSource(shader_id, 1, &source_chars, NULL);

	glCompileShader(shader_id);

	GLint isCompiled = 0;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader_id, maxLength, &maxLength, &errorLog[0]);
		// Provide the infolog in whatever manor you deem best.

		// Exit with failure.
		glDeleteShader(shader_id); // Don't leak the shader.

		return NULL_SHADER_ID;
	}

	return shader_id;
}

GLuint Shader::create_program(GLuint frag_id, GLuint vert_id, GLuint geom_id)
{
	GLuint program_id = glCreateProgram();
	if (frag_id != NULL_SHADER_ID) glAttachShader(program_id, frag_id);
	if (vert_id != NULL_SHADER_ID) glAttachShader(program_id, vert_id); // ERROR CATCHING
	if (geom_id != NULL_SHADER_ID) glAttachShader(program_id, geom_id);

	glLinkProgram(program_id);

	// print linking errors if any
	GLint success = 0;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &errorLog[0]);
		// Provide the infolog in whatever manor you deem best.

		// Exit with failure.
		glDeleteProgram(program_id); // Don't leak the shader.

		return NULL_SHADER_ID;
	}

	// delete the shaders as they're linked into our program now and no longer necessery

	if (frag_id != NULL_SHADER_ID)
		glDeleteShader(frag_id);
	if (vert_id != NULL_SHADER_ID)
		glDeleteShader(vert_id);
	if (geom_id != NULL_SHADER_ID)
		glDeleteShader(geom_id);

	return program_id;
}

Shader::~Shader()
{
	if (program_id != NULL_SHADER_ID)
		glDeleteProgram(program_id);
}

// These are here for right now, may change to diff system later

void Shader::upload_uniform_matrix4(std::string uniform_name, const GLfloat *matrix)
{
	GLint location = get_uniform_location(uniform_name);
	glUniformMatrix4fv(location, 1, GL_TRUE, matrix);
}

GLint Shader::get_uniform_location(std::string uniform_name)
{
	if (uniform_locations.find(uniform_name) != uniform_locations.end()) {
		return uniform_locations[uniform_name];
	} else {
		GLint new_location = glGetUniformLocation(program_id, uniform_name.c_str());
		uniform_locations[uniform_name] = new_location;
		return new_location;
	}
}

