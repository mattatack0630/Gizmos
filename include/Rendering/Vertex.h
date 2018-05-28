//
// Created by mathew on 5/27/18.
//

#pragma once

#include <Linear/Linear.h>
#include <vector>
#include <Linear/Vector.h>
/*

class Vertex
{
	Vector2f Uv;
	Vector3f Pos;
	Vector3f Norm;

	Vertex(const Vector2f& Uv, const Vector3f& Pos, const Vector3f& Norm, int user_index) :
			Uv(Uv), Pos(Pos), Norm(Norm)
	{
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
	}

	bool should_merge(Vertex other)
	{
		bool same = true;

		same &= (this->Uv == other.Uv);
		same &= (this->Pos == other.Pos);
		same &= (this->Norm == other.Norm);

		return same;
	}
};*/
