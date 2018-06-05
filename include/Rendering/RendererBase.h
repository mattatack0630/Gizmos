//
// Created by mathew on 6/2/18.
//

#pragma once

#include <memory>
#include "Fbo.h"
#include "Vao.h"
#include "Uniform.h"

struct Renderable
{
	Vao vao;
	std::vector<std::shared_ptr<Uniform>> uniforms;
};

class RendererBase
{
protected:
	std::vector<Renderable> renderables;

public:
	virtual void add_renderable(Vao vao, std::vector<std::shared_ptr<Uniform>> uniforms);

	virtual void generate();

	virtual void pre_render();

	virtual void render(Fbo& fbo);

	virtual void post_render();

	virtual void destroy();
};