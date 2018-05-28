//
// Created by mathew on 5/17/18.
//

#pragma once

#include <Rendering/Vao.h>
#include <Linear/Vector.h>
#include <Linear/Linear.h>
#include <fstream>
#include <map>
#include <unordered_map>

class ModelLoader
{
public:
	static Vao load_OBJ(std::string file_name);

	static Vao load_STL(std::string file_name);

	static Vao load_LIMF(std::string file_name);

	static Vao load_Wave(std::string file_name);

	static Vao load_from_arrays(std::vector<Vector3f> positions, std::vector<Vector2f> textures, std::vector<Vector3f> normals,
								std::vector<int> positions_index, std::vector<int> textures_index, std::vector<int> normals_index);
};

struct Vector3Hasher
{
	size_t operator()(const Vector3f& m) const
	{
		// Compute individual hash values for first, second and third
		// http://stackoverflow.com/a/1646913/126995

		size_t res = 17;

		for (int y = 0; y < 3; y++)
			res = res * 31 + std::hash<float>()(m.get_element(y));

		return res;
	}
};

struct Vertex
{
	bool active;
	Vector2f Uv;
	Vector3f Pos;
	Vector3f Norm;
	std::vector<int> user_indices;

	Vertex(const Vector2f& Uv, const Vector3f& Pos, const Vector3f& Norm, int user_index) :
			Uv(Uv), Pos(Pos), Norm(Norm), active(true)
	{
		user_indices.push_back(user_index);
	}

	void merge(Vertex& other)
	{
		// Average Values
		linear::add(this->Norm, other.Norm, this->Norm);
		linear::add(this->Pos, other.Pos, this->Pos);
		linear::add(this->Uv, other.Uv, this->Uv);

		linear::scale(this->Norm, 0.5, this->Norm);
		linear::scale(this->Pos, 0.5, this->Pos);
		linear::scale(this->Uv, 0.5, this->Uv);

		// Copy others users into this vertex's users
		user_indices.insert(user_indices.end(), other.user_indices.begin(), other.user_indices.end());
	}

	bool should_merge(Vertex other)
	{
		bool same = true;

		same &= (this->Uv == other.Uv);
		same &= (this->Pos == other.Pos);
		same &= (this->Norm == other.Norm); // Make this angle based tolerant later

		return same;
	}
};
