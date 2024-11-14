#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "stb_image.h"

#include <glad/glad.h>
#include <glfw3.h>

class Texture
{
private:
	GLuint m_ID;
	GLint m_wrapS;
	GLint m_wrapT;
	GLint m_minFilter;
	GLint m_magFilter;
	GLenum m_format;

public:
	Texture(std::string_view texFile, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, GLenum format)
		: m_wrapS{ wrapS }
		, m_wrapT{ wrapT }
		, m_minFilter{ minFilter }
		, m_magFilter{ magFilter }
		, m_format{ format }
	{
		// Create and Bind Texture
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// Set Paramaters for Texture
		setParameters();

		// Generate Texture From File
		generateTexture(texFile);

		// Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint getID() const { return m_ID; }
	const GLuint* getIDPointer() const { return &m_ID; }

private:
	void setParameters()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);
	}

	void generateTexture(std::string_view texFile)
	{
		// load and generate the texture
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(texFile.data(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cerr << "ERROR: Texture::generateTexture() failed to load texture: " 
				<< stbi_failure_reason() << '\n';
		}
		stbi_image_free(data);
	}


};

#endif