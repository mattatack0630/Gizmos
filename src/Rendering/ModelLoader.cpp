//
// Created by mathew on 5/27/18.
//
#include "Rendering/ModelLoader.h"

void read_OBJ_input(std::ifstream& input, std::vector<Vector3f>& pos, std::vector<Vector2f>& texts, std::vector<Vector3f>& norms,
					std::vector<int>& positions_index, std::vector<int>& textures_index, std::vector<int>& normals_index)
{

	while (input.peek() != EOF) {
		std::string name = "";
		float x = 0;
		float y = 0;
		float z = 0;

		input >> name;

		if (name == "v") {
			input >> x;
			input >> y;
			input >> z;
			pos.push_back(Vector3f({x, y, z}));
		}

		if (name == "vn") {
			input >> x;
			input >> y;
			input >> z;
			norms.push_back(Vector3f({x, y, z}));
		}

		if (name == "vt") {
			input >> x;
			input >> y;
			texts.push_back(Vector2f({x, y}));
		}

		if (name == "f") {
			for (int i = 0; i < 3; i++) {
				std::string v1;
				input >> v1;

				int t;
				int p;
				int n;
				int del_pos1 = v1.find("/", 0);
				int del_pos2 = v1.find("/", del_pos1 + 1);

				p = std::stoi(v1.substr(0, del_pos1));
				t = std::stoi(v1.substr(del_pos1 + 1, del_pos2 - del_pos1 - 1));
				n = std::stoi(v1.substr(del_pos2 + 1, v1.length() - del_pos2 - 1));

				positions_index.push_back(p - 1);
				textures_index.push_back(t - 1);
				normals_index.push_back(n - 1);
			}
		}
	}
}

void create_map(std::unordered_map<Vector3f, std::vector<Vertex>, Vector3Hasher>& vertex_map,
				std::vector<Vector3f>& positions, std::vector<Vector2f>& textures, std::vector<Vector3f>& normals,
				std::vector<int>& positions_index, std::vector<int>& textures_index, std::vector<int>& normals_index)
{
	for (int i = 0; i < positions_index.size(); i++) {
		int p_index = positions_index[i];
		int t_index = textures_index[i];
		int n_index = normals_index[i];
		Vector3f p = positions[p_index];
		Vector2f t = textures[t_index];
		Vector3f n = normals[n_index];

		if (vertex_map.find(p) == vertex_map.end()) {
			vertex_map[p] = std::vector<Vertex>();
		}

		vertex_map[p].push_back(Vertex(t, p, n, i));
	}
}

void merge_duplicates(std::unordered_map<Vector3f, std::vector<Vertex>, Vector3Hasher>& vertex_map)
{
	for (auto& entry : vertex_map) {
		std::vector<Vertex>& list = entry.second;
		for (int i = 0; i != list.size(); i++) {
			for (int j = 0; j < list.size(); j++) {
				Vertex& v1 = list.at(i);
				Vertex& v2 = list.at(j);
				if (i != j && v1.should_merge(v2) && v1.active) {
					v1.merge(v2);
					v2.active = false;
				}
			}
		}
	}

	for (auto& entry : vertex_map) {
		std::vector<Vertex>& list = entry.second;
		for (int i = list.size() - 1; i >= 0; i--) {
			if (!list.at(i).active)
				list.erase(list.begin() + i);
		}
	}
}

void convert_to_arrays(std::unordered_map<Vector3f, std::vector<Vertex>, Vector3Hasher>& vertex_map, std::vector<float>& vertex,
					   std::vector<int>& vertex_index, int v_count)
{
	vertex_index.resize(v_count);

	int count = 0;

	for (auto& entry : vertex_map) {
		std::vector<Vertex>& list = entry.second;

		for (int i = 0; i < list.size(); i++) {

			for (int j :  list.at(i).user_indices)
				vertex_index.at(j) = count;
			count++;

			vertex.push_back(list.at(i).Pos.get_element(0));
			vertex.push_back(list.at(i).Pos.get_element(1));
			vertex.push_back(list.at(i).Pos.get_element(2));

			vertex.push_back(list.at(i).Norm.get_element(0));
			vertex.push_back(list.at(i).Norm.get_element(1));
			vertex.push_back(list.at(i).Norm.get_element(2));

			vertex.push_back(list.at(i).Uv.get_element(0));
			vertex.push_back(list.at(i).Uv.get_element(1));
		}
	}


}

void build_vao(Vao& vert_array, std::vector<float>& vertex, std::vector<int>& vertex_index)
{
	Vbo vert_buffer = Vbo(vertex.data(), 8 * sizeof(GLfloat), vertex_index.size());
	vert_buffer.set_attrib_pointer(0, 3, GL_FLOAT, 0 * sizeof(GLfloat));
	vert_buffer.set_attrib_pointer(1, 3, GL_FLOAT, 3 * sizeof(GLfloat));
	vert_buffer.set_attrib_pointer(2, 2, GL_FLOAT, 6 * sizeof(GLfloat));

	Vbo index_buffer = Vbo(vertex_index.data(), 1 * sizeof(GLuint), vertex_index.size(), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

	vert_array.add_data_vbo(vert_buffer);
	vert_array.add_index_vbo(index_buffer);
	vert_array.set_vertex_count(vertex_index.size());
}

Vao ModelLoader::load_from_arrays(std::vector<Vector3f> positions, std::vector<Vector2f> textures, std::vector<Vector3f> normals,
								  std::vector<int> positions_index, std::vector<int> textures_index, std::vector<int> normals_index)
{
	Vao vert_array = Vao();
	std::vector<float> vertex;
	std::vector<int> vertex_index;
	std::unordered_map<Vector3f, std::vector<Vertex>, Vector3Hasher> vertex_map;

	create_map(vertex_map, positions, textures, normals, positions_index, textures_index, normals_index);

	merge_duplicates(vertex_map);

	convert_to_arrays(vertex_map, vertex, vertex_index, positions_index.size());

	build_vao(vert_array, vertex, vertex_index);

	return vert_array;
}

Vao ModelLoader::load_OBJ(std::string file_name)
{
	std::vector<Vector3f> positions;
	std::vector<Vector2f> textures;
	std::vector<Vector3f> normals;

	std::vector<int> positions_index;
	std::vector<int> textures_index;
	std::vector<int> normals_index;

	std::ifstream input = std::ifstream(file_name);

	read_OBJ_input(input, positions, textures, normals, positions_index, textures_index, normals_index);

	return load_from_arrays(positions, textures, normals, positions_index, textures_index, normals_index);
}