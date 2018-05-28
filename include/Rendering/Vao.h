//
// Created by mathew on 5/17/18.
//

#pragma once

#include <vector>
#include "Vbo.h"

class Vao
{
private:
	GLuint vao_id;
	GLuint topology;
	GLuint vert_count;
	std::vector<Vbo> vbos;

public:
	Vao();
	Vao(GLuint topology);
	~Vao();

	void add_data_vbo(Vbo);
	void add_index_vbo(Vbo);

	GLuint get_vertex_count();
	void set_vertex_count(GLuint i);

	GLuint get_topology();

	void bind();
	void unbind();
};
