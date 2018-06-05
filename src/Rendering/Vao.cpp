//
// Created by mathew on 5/17/18.
//
#include <Rendering/Vao.h>
#include <Rendering/GLErrorCall.h>
// Oh this needs to be fixed pronto! LEAKS TODO
Vao::Vao() : Vao(GL_TRIANGLES)
{
}

Vao::Vao(GLuint topology)
{
	this->topology = topology;
	GLCall(glGenVertexArrays(1, &vao_id));
	GLCall(glBindVertexArray(vao_id));
}

void Vao::add_data_vbo(Vbo vbo)
{
	//check already in
	vbos.push_back(vbo);

	//check if already bound
	GLCall(glBindVertexArray(vao_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo_id));

	for(int i = 0; i<vbo.attribs.size(); i++) {
		auto attrib = vbo.attribs.at(i);
		GLCall(glEnableVertexAttribArray(attrib.index));
		GLCall(glVertexAttribPointer(attrib.index, attrib.components, attrib.type, GL_FALSE, vbo.chunk_size, (GLuint *) attrib.offset));
	}

}

void Vao::add_index_vbo(Vbo vbo)
{
	//check already in
	vbos.push_back(vbo);
}

void Vao::bind()
{
	//check if already bound
	GLCall(glBindVertexArray(vao_id));
	for(Vbo vbo : vbos) {
		vbo.bind();
		for (int i = 0; i < vbo.attribs.size(); i++) {
			auto attrib = vbo.attribs.at(i);
			GLCall(glEnableVertexAttribArray(attrib.index));
		}
	}
}

void Vao::unbind()
{
	//check if already bound
	for(Vbo vbo : vbos) {
		vbo.unbind();
		for (int i = 0; i < vbo.attribs.size(); i++) {
			auto attrib = vbo.attribs.at(i);
			GLCall(glDisableVertexAttribArray(attrib.index));
		}
	}
}

void Vao::generate()
{
}

void Vao::destroy()
{
	for(Vbo vbo : vbos) {
		vbo.destroy();
	}

	GLCall(glDeleteVertexArrays(1, &vao_id));
}

GLuint Vao::get_vertex_count()
{
	return vert_count;
}

void Vao::set_vertex_count(GLuint count)
{
	vert_count = count;
}

GLuint Vao::get_topology()
{
	return topology;
}

GLuint Vao::get_id()
{
	return vao_id;
}