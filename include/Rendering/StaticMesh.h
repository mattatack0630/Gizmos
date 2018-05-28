//
// Created by mathew on 5/27/18.
//
// Do not use for efficiency, this is a good object for simple model
// procedural generation, its not meant to be fast
//

#pragma once

#include <Rendering/Vao.h>
#include <Linear/Vector.h>
#include "Vertex.h"

class StaticMesh
{
	std::vector<GLfloat> vertices;
	std::vector<GLuint> vertices_index;
	GLuint vertex_prediction;
	GLuint topology;
	GLuint vert_count;

public:
	StaticMesh(GLuint vertex_prediction, GLuint topology);

	void start();

	void vertex(Vector3f position, Vector3f normal, Vector2f texture);

	void vertex(GLfloat px, GLfloat py, GLfloat pz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat tx, GLfloat ty);

	void finish();

	Vao to_vao(); //  Too many objects know about VAOs, maybe decouple these
};