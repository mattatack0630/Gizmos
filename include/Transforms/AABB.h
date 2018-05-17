//
// Created by mathew on 5/6/18.
//

#pragma once

class AABB
{
public:
	float min_x, min_y, min_z;
	float max_x, max_y, max_z;

	AABB(float min_x, float min_y, float min_z, float max_x, float max_y, float max_z) :
			min_x(min_x),
			min_y(min_y),
			min_z(min_z),
			max_x(max_x),
			max_y(max_y),
			max_z(max_z)
	{
	}
};
