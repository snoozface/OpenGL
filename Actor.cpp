#include "Actor.h"

#include <cmath>

// Static variable initializations

// Variable m_maxTextureUnits holds the maximum amount of texture units
// which varies based on GPU
// m_maxTextureUnits is set once upon creation of the first Actor made
// during runtime
// Changed to default to 16 instead of max for GPU
size_t Actor::m_maxTextureUnits = 16;
bool Actor::m_isFirstActor = true;

// Constructor
Actor::Actor()
{
	// Get max number of texture units if it's the first Actor constructed
	// Not currently using, set max number of textures to 16 to suit fragment shader texture array
	//if (m_isFirstActor)
	//{
	//	GLint maxTextureUnits;
	//	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
	//	m_maxTextureUnits = static_cast<size_t>(maxTextureUnits);
	//	m_isFirstActor = false;
	//}

	// Create Shared Pointers to Derived Buffer Class Objects
	m_EBO = std::make_shared<EBO>(Buffer::Type::EBO);
	m_VBOPos = std::make_shared<VBO>(Buffer::Type::VBOPos);
	m_VBOColor = std::make_shared<VBO>(Buffer::Type::VBOColor);
	m_VBOTexCoord = std::make_shared<VBO>(Buffer::Type::VBOTexCoord);
	// Create Shared Pointers to the Base Buffer Objects and store in m_buffers
	m_buffers[Buffer::Type::EBO] = { m_EBO };
	m_buffers[Buffer::Type::VBOPos] = { m_VBOPos };
	m_buffers[Buffer::Type::VBOColor] = { m_VBOColor };
	m_buffers[Buffer::Type::VBOTexCoord] = { m_VBOTexCoord };
}

Actor::~Actor()
{
	for (Texture& texture : m_textures)
		glDeleteTextures(1, texture.getIDPointer());
}

std::shared_ptr<VBO> Actor::getVBOPointer(Buffer::Type type) const
{
	switch (type)
	{
	case Buffer::Type::VBOPos:
		return m_VBOPos;
	case Buffer::Type::VBOColor:
		return m_VBOColor;
	case Buffer::Type::VBOTexCoord:
		return m_VBOTexCoord;
	default:
		std::cerr << "ERROR: Actor::getBufferPointer() called with invalid type\n";
		return nullptr;
	}
}

void Actor::linkVertexAttributes(Buffer::Type bufferType, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	m_VAO.bindVAO();
	switch (bufferType)
	{
	case Buffer::Type::VBOPos:
		m_VBOPos->bindBuffer();
		break;
	case Buffer::Type::VBOColor:
		m_VBOColor->bindBuffer();
		break;
	case Buffer::Type::VBOTexCoord:
		m_VBOTexCoord->bindBuffer();
		break;
	default:
		std::cerr << "ERROR: Actor::linkVertexAttributes() called with invalid Type\n";
	}
	m_VAO.linkVertexAttributes(location, size, type, normalized, stride, offset);
	m_VAO.unbindVAO();
}

// Bind/Unbind Buffer
void Actor::bindBuffer(Buffer::Type type)
{
	switch (type)
	{
	case Buffer::Type::EBO:
		m_VAO.bindVAO();
		m_EBO->bindBuffer();
		break;
	case Buffer::Type::VBOPos:
		m_VAO.bindVAO();
		m_VBOPos->bindBuffer();
		break;
	case Buffer::Type::VBOColor:
		m_VAO.bindVAO();
		m_VBOColor->bindBuffer();
		break;
	case Buffer::Type::VBOTexCoord:
		m_VAO.bindVAO();
		m_VBOTexCoord->bindBuffer();
		break;
	default:
		std::cerr << "ERROR: Actor::bindBuffer() called with invalid Type\n";
		break;
	}
}

/*
* uploadBuffers()
*
* If not using an EBO, must use std::vector<int>() as first
* parameter.
*
* Sets m_count to the amount of vertices in posData
* Takes separate data vectors for each buffer and uploads
* them all at once.
*/
void Actor::uploadBuffers(const std::vector<int>& eboData,
				const std::vector<float>& posData,
				const std::vector<float>& colorData,
				const std::vector<float>& texCoordData)
{
	// Store the size of the posData as m_count
	// Divided by 3 to get the number of vertices
	// Because each vertex has 3 components
	// 
	// Potential bug - on some systems size_t may be 64-bit and GLsizei is always 32-bit
	// If a very large amount of data is uploaded to the VBOPos, it could potentially
	// overflow the GLsizei
	m_count = static_cast<GLsizei>(posData.size() / 3);
	m_VAO.bindVAO();
	if (!eboData.empty())
	{
		m_drawType = Elements;
		m_EBO->bindBuffer();
		m_EBO->uploadBuffer(eboData, m_usage);
	}
	if (!posData.empty())
	{
		m_VBOPos->bindBuffer();
		m_VBOPos->uploadBuffer(posData, m_usage);
	}
	if (!colorData.empty())
	{
		m_VBOColor->bindBuffer();
		m_VBOColor->uploadBuffer(colorData, m_usage);
	}
	if (!texCoordData.empty())
	{
		m_VBOTexCoord->bindBuffer();
		m_VBOTexCoord->uploadBuffer(texCoordData, m_usage);
	}
	m_VAO.unbindVAO();
}


void Actor::render(GLenum mode)
{
	m_VAO.bindVAO();
	m_shader->useShaderProgram();
	bindTextures();

	switch (m_drawType)
	{
	case Arrays:
		drawArrays(mode);
		break;
	case Elements:
		drawElements(mode);
		break;
	default:
		std::cerr << "Actor::render() called with unknown DrawType\n";
		break;
	}

	m_VAO.unbindVAO();
	unbindTextures();
}

void Actor::drawArrays(GLenum mode)
{
	glDrawArrays(mode, 0, m_count);
}

void Actor::drawElements(GLenum mode)
{
	glDrawElements(mode, static_cast<GLsizei>(m_EBO->getData().size()), GL_UNSIGNED_INT, 0);
}
