//
// Created by mathew on 6/2/18.
//

#include <Rendering/RendererBase.h>

void RendererBase::generate()
{

}

void RendererBase::pre_render()
{

}

void RendererBase::render(Fbo& fbo)
{

}

void RendererBase::post_render()
{
	renderables.clear();
}

void RendererBase::destroy()
{

}

void RendererBase::add_renderable(Vao vao, std::vector<std::shared_ptr<Uniform>> uniforms)
{
	renderables.push_back({vao, uniforms});
}
