//
// Created by mathew on 5/29/18.
//

#include <Rendering/Texture2D.h>
#include <Rendering/GLErrorCall.h>
#include "Rendering/Fbo.h"

RenderTextureAttachment::RenderTextureAttachment(int attach_loc)
{
	this->attach_loc = attach_loc;
	this->attachment_id = 0;
	this->internal_format = GL_RGB;
	this->write_format = GL_RGB;
	this->write_type = GL_UNSIGNED_BYTE;
}

RenderTextureAttachment::RenderTextureAttachment(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type)
{
	this->attach_loc = attach_loc;
	this->attachment_id = 0;
	this->internal_format = internal_format;
	this->write_format = write_format;
	this->write_type = write_type;
}

void RenderTextureAttachment::generate(int w, int h)
{
	GLCall(glGenTextures(1, &attachment_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, attachment_id));
	// Active Texture
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internal_format, w, h, 0, write_format, write_type, nullptr));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
}

void RenderTextureAttachment::attach_to(Fbo& fbo)
{
	GLCall(glBindTexture(GL_TEXTURE_2D, attachment_id));
	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attach_loc, attachment_id, 0));
}

void RenderTextureAttachment::destroy()
{
	GLCall(glDeleteTextures(1, &attachment_id));
}

////////////////////////////////////////////////////////////

DepthBufferAttachment::DepthBufferAttachment()
{

}

void DepthBufferAttachment::generate(int w, int h)
{
	GLCall(glGenRenderbuffers(1, &attachment_id));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, attachment_id));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h));
}

void DepthBufferAttachment::attach_to(Fbo& fbo)
{
	fbo.bind();
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, attachment_id));
}

void DepthBufferAttachment::destroy()
{
	GLCall(glDeleteRenderbuffers(1, &attachment_id));
}

////////////////////////////////////////////////////////////

RenderBufferAttachment::RenderBufferAttachment(int attach_loc)
{
	this->attach_loc = attach_loc;
	this->attachment_id = 0;
	this->internal_format = GL_RGBA;
	this->write_format = GL_RGBA;
	this->write_type = GL_UNSIGNED_BYTE;
}

RenderBufferAttachment::RenderBufferAttachment(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type)
{
	this->attach_loc = attach_loc;
	this->attachment_id = 0;
	this->internal_format = internal_format;
	this->write_format = write_format;
	this->write_type = write_type;
}

void RenderBufferAttachment::generate(int w, int h)
{
	GLCall(glGenRenderbuffers(1, &attachment_id));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, attachment_id));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, internal_format, w, h));
}

void RenderBufferAttachment::attach_to(Fbo& fbo)
{
	fbo.bind();
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attach_loc, GL_RENDERBUFFER, attachment_id));
}

void RenderBufferAttachment::destroy()
{
	GLCall(glDeleteRenderbuffers(1, &attachment_id));
}

////////////////////////////////////////////////////////////

Fbo::Fbo(GLuint w, GLuint h)
{
	this->width = w;
	this->height = h;

}

Fbo::Fbo(GLuint w, GLuint h, GLuint id)
{
	this->width = w;
	this->height = h;
	this->fbo_id = id;
}

void Fbo::bind() const
{
	// bind attachments
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo_id));
	GLCall(glViewport(0, 0, width, height));
}

void Fbo::unbind() const
{
	// unbind attachments
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GLuint Fbo::get_id() const
{
	return fbo_id;
}

void Fbo::generate()
{
	// Move somewhere else
	GLCall(glGenFramebuffers(1, &fbo_id));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo_id));

	for (Attachment* attachment : attachments) {
		attachment->generate(width, height);
		attachment->attach_to(*this);
	}

	GLCall(glDrawBuffers(draw_buffers.size(), draw_buffers.data()));

	// unbind
}

void Fbo::destroy()
{
	while (attachments.empty()) {
		Attachment* a = attachments.back();
		attachments.pop_back();
		a->destroy();
		delete a; //  Smart pointer later
	}

	GLCall(glDeleteFramebuffers(1, &fbo_id));
}

void Fbo::attach_render_texture(GLuint target_loc)
{
	Attachment* attachment = new RenderTextureAttachment(target_loc);
	attachments.push_back(attachment);
	draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + target_loc);
}

void Fbo::attach_render_texture(int attach_loc, GLuint internal_format, GLuint write_format, GLuint write_type)
{
	Attachment* attachment = new RenderTextureAttachment(attach_loc, internal_format, write_format, write_type);
	attachments.push_back(attachment);
	draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + attach_loc);
}

void Fbo::attach_depth_buffer()
{
	Attachment* attachment = new DepthBufferAttachment();
	attachments.push_back(attachment);
}

void Fbo::attach_render_buffer(GLuint target_loc)
{
	Attachment* attachment = new RenderBufferAttachment(target_loc);
	attachments.push_back(attachment);
	draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + target_loc);
}

GLuint Fbo::get_attachment(int i)
{
	return attachments.at(i)->attachment_id;

}