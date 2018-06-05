//
// Created by mathew on 6/3/18.
//

#pragma once

#include "Vertex.h"

class DirectionLight
{
	public:
		Vector3f color;
		Vector3f direction;

		DirectionLight(Vector3f color, Vector3f dir) :
				color(color),
				direction(dir)
		{

		}
};

class PointLight
{
	public:
		Vector3f color;
		Vector3f position;
		Vector3f attenuation;

		PointLight(Vector3f color, Vector3f pos, Vector3f att) :
				color(color),
				position(pos),
				attenuation(att)
		{

		}
};

class SpotLight
{
	public:
		Vector3f color;

		SpotLight(Vector3f color) :
				color(color)
		{

		}
};

class AmbientLight
{
	public:
		Vector3f color;

		AmbientLight(Vector3f color) :
				color(color)
		{

		}
};