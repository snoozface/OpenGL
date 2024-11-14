#ifndef ACTOR_H
#define ACTOR_H

#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VBO.h"
#include "EBO.h"

#include "stb_image.h"

#include <memory>			// for std::shared_ptr
#include <unordered_map>	// for std::unordered_map


#include <string>

class Actor
{
public:
	enum DrawType {
		Arrays,
		Elements
	};
private:

	//*******************************************************************************
	//*******************************************************************************
	// Member Variables

	// VAO - automatically generated and owned by Actor
	VertexArray m_VAO{};

	//*******************************************************************************
	// ****Buffers****
	// 
	// All buffers are generated in Actor constructor

	// Unordered Map of Base Class Buffer Pointers
	// Contains EBO and all VBOs
	std::unordered_map<Buffer::Type, std::shared_ptr<Buffer>> m_buffers;

	// EBO
	std::shared_ptr<EBO> m_EBO;

	// Position VBO
	std::shared_ptr<VBO> m_VBOPos;

	// Color VBO
	std::shared_ptr<VBO> m_VBOColor;

	// TexCoord VBO
	std::shared_ptr<VBO> m_VBOTexCoord;

	// m_count contains the number of vertices in the buffer
	// m_count = m_VBOPos.size() / 3 because each vertex has 3 components
	// Set by Actor::uploadBuffers()
	// Used for glDrawArrays count argument
	GLsizei m_count{};

	//*******************************************************************************
	// ****Textures****

	// Vector of Textures
	std::vector<Texture> m_textures;

	// Variable m_maxTextureUnits holds the maximum amount of texture units
	// which varies based on GPU
	// m_maxTextureUnits is set once upon creation of the first Actor made
	// during runtime
	static size_t m_maxTextureUnits;
	static bool m_isFirstActor;


	//*******************************************************************************
	// ****Rendering****

	// Pointer to shader used by Actor
	// Must be set by Actor::connectShader before calling Actor::render
	Shader* m_shader{ nullptr };

	// DrawType used to select DrawArrays or DrawElements
	// Arrays by default, changes to Elements if Actor::uploadBuffer
	// or Actor::uploadBuffers are called
	DrawType m_drawType{ Arrays };		


	// Variables used for glBufferData (Buffer::uploadBuffer)
	// usage: STREAM, STATIC, or DYNAMIC
	// nature: DRAW, READ, COPY
	// GL_STATIC_DRAW by default, use setter to change
	// Passed to Buffer through Actor::uploadBuffer and Actor::uploadBuffers
	GLenum m_usage{ GL_STATIC_DRAW };

public:

	void printTexture()
	{
		for (Texture& texture : m_textures)
		{
			std::cout << "Texture ID: " << texture.getID() << '\n';
		}
	}

	//*******************************************************************************
	//*******************************************************************************
	// Member Functions

	/*
	* Actor() Constructor
	* 
	* Generates VAO and all Buffers
	* Populates m_buffers with std::shared_ptr<Buffer> to each Buffer
	*/
	Actor();
	~Actor();


	// ***************************************************
	// Getters

	std::shared_ptr<EBO> getEBOPointer() const { return m_EBO; }
	std::shared_ptr<VBO> getVBOPointer(Buffer::Type type) const;


	// ***************************************************
	// Data Management

	// ***************************************************
	// Textures
	
	// Add Texture
	void addTexture(std::string_view texFile, GLint wrapS, GLint wrapT, GLint minFilter, GLint magFilter, GLenum format)
	{
		if (m_textures.size() < m_maxTextureUnits)
		{
			Texture texture(texFile, wrapS, wrapT, minFilter, magFilter, format);
			m_textures.emplace_back(texture);
		}
		else
		{
			std::cerr << "ERROR: Actor::addTexture: New texture not added. Max amount already reached.\n";
		}

	}


	/*
	* This function is used to set the uniforms of all textures at once
	* Use function after all textures have been added with Actor::addTexture()
	* 
	* Requires the following uniforms to be in the fragment shader:
	* uniform sampler2D textures[16];
	* uniform int numTextures;
	*/
	void setTextureUniforms()
	{
		m_shader->useShaderProgram();
		m_shader->setUniformInt1("numTextures", static_cast<int>(m_textures.size()));

		for (size_t i = 0; i < m_textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			glBindTexture(GL_TEXTURE_2D, m_textures[i].getID());
			std::string samplerName = "textures[" + std::to_string(i) + "]";
			m_shader->setUniformInt1(samplerName, static_cast<GLint>(i));
		}
	}

	// Bind/Unbind Textures
	void bindTextures()
	{
		for (size_t i{0}; i < m_textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			glBindTexture(GL_TEXTURE_2D, m_textures[i].getID());
		}
	}
	void unbindTextures()
	{
		for (size_t i{ 0 }; i < m_textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}



	// ***************************************************
	// VAO

private:
	// Bind/Unbind VAO
	void bindVAO() { m_VAO.bindVAO(); }
	void unbindVAO() { m_VAO.unbindVAO(); }

public:
	// Link Vertex Attributes
	void linkVertexAttributes(Buffer::Type bufferType, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

	// VAO Getters
	GLuint getVAOID() { return m_VAO.getID(); }
	const VertexArray& getVAO() const { return m_VAO; }


	// ***************************************************
	// Buffers

private:
	// Bind/Unbind Buffer
	void bindBuffer(Buffer::Type type);

public:
	// uploadBuffer
	// This function uploads one buffer individually
	// Probably... hasn't been tested....
	template <typename T>
	void uploadBuffer(Buffer::Type type, std::vector<T> data)
	{
		m_VAO.bindVAO();
		switch (type)
		{
		case Buffer::Type::EBO:
			m_drawType = Elements;
			m_EBO->bindBuffer();
			m_EBO->uploadBuffer(data, m_usage);
			break;
		case Buffer::Type::VBOPos:
			m_VBOPos->bindBuffer();
			m_VBOPos->uploadBuffer(data, m_usage);
			break;
		case Buffer::Type::VBOColor:
			m_VBOColor->bindBuffer();
			m_VBOColor->uploadBuffer(data, m_usage);
			break;
		case Buffer::Type::VBOTexCoord:
			m_VBOTexCoord->bindBuffer();
			m_VBOTexCoord->uploadBuffer(data, m_usage);
			break;
		default:
			std::cerr << "ERROR: Actor::uploadBuffer() called with invalid Type\n";
			break;
		}
	}

	/*
	* uploadBuffers
	* This function uploads all buffers at once
	* 
	* If not using an EBO, must use std::vector<int>() as first
	* parameter.
	* 
	* Sets m_count to the amount of vertices in posData
	* Takes separate data vectors for each buffer
	*/
	void uploadBuffers(const std::vector<int>& eboData = std::vector<int>(),
		const std::vector<float>& posData = std::vector<float>(),
		const std::vector<float>& colorData = std::vector<float>(),
		const std::vector<float>& texCoordData = std::vector<float>());


	// ***************************************************
	// Shader

public:
	// Link Shader Program to this Actor
	void connectShader(Shader* shader) { m_shader = shader; }


	//*******************************************************************************
	// ******************************************************************************
	// Rendering Functions

public:
	void render(GLenum mode);

private:
	// drawArrays is called by render() if no data was uploaded to EBO
	void drawArrays(GLenum mode);

	// drawElements is called by render() if data was uploaded to EBO
	void drawElements(GLenum mode);


	//*******************************************************************************
	// ******************************************************************************
	// glBufferData
public:
	GLenum getUsage() { return m_usage; }
	void setUsage(GLenum usage) { m_usage = usage; }
};



#endif