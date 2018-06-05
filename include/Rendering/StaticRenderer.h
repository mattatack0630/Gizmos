//
// Created by mathew on 6/2/18.
//

#pragma once

#include <fstream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <Transforms/PerspectiveTransform.h>
#include <Transforms/WorldTransform.h>
#include "RendererBase.h"
#include "Shader.h"
#include "Vertex.h"
#include "Light.h"

class StaticRenderer : public RendererBase
{
	std::vector<DirectionLight> direction_lights;
	std::vector<PointLight> point_lights;
	std::vector<SpotLight> spot_lights;

	std::unique_ptr<Shader> shader_g_buffer;
	std::unique_ptr<Shader> shader_lighting;

	std::unique_ptr<Fbo> fbo_g_buffer;
	std::unique_ptr<Fbo> fbo_lighting;

	Vao screen_quad; // CANNOT DO THIS
	Vao sphere_vao; // CANNOT DO THIS

public:
	StaticRenderer();

	void generate() override;

	void pre_render() override;

	void render(Fbo& fbo) override;

	void post_render() override;

	void destroy() override;

	void add_spot_light(SpotLight l);
	void add_point_light(PointLight l);
	void add_direction_light(DirectionLight l);
};