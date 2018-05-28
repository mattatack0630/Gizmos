//
// Created by mathew on 5/27/18.
//

#include "Rendering/StaticMesh.h"

StaticMesh::StaticMesh(GLuint vertex_prediction, GLuint topology) :
		topology(topology),
		vert_count(0)
{

}

void StaticMesh::start()
{
	vertices.clear();
}

void StaticMesh::vertex(Vector3f position, Vector3f normal, Vector2f texture)
{
	vertices.push_back(position.get_element(0));
	vertices.push_back(position.get_element(1));
	vertices.push_back(position.get_element(2));

	vertices.push_back(normal.get_element(1));
	vertices.push_back(normal.get_element(2));
	vertices.push_back(normal.get_element(3));

	vertices.push_back(texture.get_element(0));
	vertices.push_back(texture.get_element(1));

	vertices_index.push_back(vert_count);

	vert_count += 1;
}

void StaticMesh::vertex(GLfloat px, GLfloat py, GLfloat pz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty)
{
	vertices.push_back(px);
	vertices.push_back(py);
	vertices.push_back(pz);

	vertices.push_back(nx);
	vertices.push_back(ny);
	vertices.push_back(nz);

	vertices.push_back(tx);
	vertices.push_back(ty);

	vertices_index.push_back(vert_count);

	vert_count += 1;
}

void StaticMesh::finish()
{
	// Something here
}

Vao StaticMesh::to_vao()
{
	Vao vert_array = Vao(topology);

	Vbo vert_buffer = Vbo(vertices.data(), 8 * sizeof(GLfloat), vertices_index.size());
	vert_buffer.set_attrib_pointer(0, 3, GL_FLOAT, 0 * sizeof(GLfloat));
	vert_buffer.set_attrib_pointer(1, 3, GL_FLOAT, 3 * sizeof(GLfloat));
	vert_buffer.set_attrib_pointer(2, 2, GL_FLOAT, 6 * sizeof(GLfloat));

	Vbo index_buffer = Vbo(vertices_index.data(), 1 * sizeof(GLuint), vertices_index.size(), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	vert_array.add_data_vbo(vert_buffer);
	vert_array.add_index_vbo(index_buffer);
	vert_array.set_vertex_count(vert_count);

	return vert_array;
}
