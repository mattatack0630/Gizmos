//
// Created by mathew on 5/29/18.
//

#pragma once

#include <vector>
#include "../../lib/glfw/deps/glad/glad.h"

class Fbo; // Forward

class Attachment
{
public:
	GLuint attachment_id;

	virtual void generate(int w, int h) = 0;

	virtual void attach_to(Fbo& fbo) = 0;

	virtual void destroy() = 0;
};

class RenderTextureAttachment : public Attachment
{
private:
	int attach_loc;
	int internal_format;
	int write_format;
	int write_type;

public:
	RenderTextureAttachment(int attach_loc);

	RenderTextureAttachment(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type);

	void generate(int w, int h) override;

	void attach_to(Fbo& fbo) override;

	void destroy() override;
};

class DepthBufferAttachment : public Attachment
{
public:
	DepthBufferAttachment();

	void generate(int w, int h) override;

	void attach_to(Fbo& fbo) override;

	void destroy() override;
};

class RenderBufferAttachment : public Attachment
{
private:
	int attach_loc;
	int internal_format;
	int write_format;
	int write_type;

public:
	RenderBufferAttachment(int attach_loc);

	RenderBufferAttachment(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type);

	void generate(int w, int h) override;

	void attach_to(Fbo& fbo) override;

	void destroy() override;
};

/*
class DepthTextureAttachment : public Attachment
{
public:
	DepthBufferAttachment();

	void generate(int w, int h) override ;
	void attach_to(Fbo& fbo) override;
	void destroy() override;
};
*/

class Fbo
{
private:
	GLuint width;
	GLuint height;
	GLuint fbo_id;

	// Make sure client doesnt regenerate fbo

	std::vector<Attachment*> attachments;
	std::vector<GLuint> draw_buffers;

	Fbo(GLuint w, GLuint h, GLuint id);

public:
	Fbo(GLuint w, GLuint h);

	void attach_render_texture(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type);

	void attach_render_texture(GLuint target_loc);

	void attach_render_buffer(GLuint target_loc);

	void attach_depth_buffer();

	void bind() const;

	void unbind() const;

	GLuint get_id() const;

	void generate();

	void destroy();

	GLuint get_attachment(int i);

	static const Fbo screen_fbo()
	{
		GLint m_viewport[4];

		glGetIntegerv(GL_VIEWPORT, m_viewport);

		return Fbo(m_viewport[2], m_viewport[3], 0);
	}
};

