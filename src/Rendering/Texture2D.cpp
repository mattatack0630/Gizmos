//
// Created by mathew on 5/29/18.
//


#include <Rendering/Texture2D.h>
#include <Rendering/GLErrorCall.h>

#define STB_IMAGE_IMPLEMENTATION

#include "../lib/others/stb_image.h"

Texture2D::Texture2D(std::string location)
{
	this->data = stbi_load(location.data(), &width, &height, &channels, 0);

}

Texture2D::Texture2D(int w, int h)
{
	this->width = w;
	this->height = h;
	this->channels = 3; // dunnp
	this->data = nullptr;
}


Texture2D::Texture2D(GLuint id, int w, int h)
{
	this->texture_id = id;
	this->width = w;
	this->height = h;
	this->data = nullptr;
}


void Texture2D::bind(GLuint spot)
{
	GLCall(glActiveTexture(GL_TEXTURE0 + spot));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture_id));
	bind_location = spot;
}

void Texture2D::unbind()
{
	//glActiveTexture(GL_TEXTURE0 + bind_location);
	//glBindTexture(GL_TEXTURE_2D, GL_NULL);
	bind_location = 0;
}

void Texture2D::generate_texture(unsigned char *data)
{
	if (data) {
		GLCall(glGenTextures(1, &texture_id));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture_id));
		// Active Texture
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D)); // Set Bool! TODO
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

}

void Texture2D::applyParameteri(GLuint name, GLuint value)
{
	bind(0); // Make sure not already
	GLCall(glTexParameteri(GL_TEXTURE_2D, name, value));
	unbind(); // Maybe not
}

GLuint Texture2D::get_bind_location()
{
	return bind_location;
}

GLuint Texture2D::get_id()
{
	return texture_id;
}

void Texture2D::generate()
{
	this->generate_texture(data);

	if (data) {
		stbi_image_free(data); // No need anymore
	}

	this->applyParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	this->applyParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	this->applyParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	this->applyParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture2D::destroy()
{
	GLCall(glDeleteTextures(1, &texture_id));
}