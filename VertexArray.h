#ifndef VAO_H
#define VAO_H

#include "Buffer.h"

#include <vector>

class VertexArray
{
private:
	GLuint m_VAOID{};
	std::vector<Buffer> m_VBOs{};
	std::vector<Buffer> m_EBOs{};

public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_VAOID);
	}

	// Bind/Unbind VAO
	void bindVAO() { glBindVertexArray(m_VAOID); }
	void unbindVAO() { glBindVertexArray(0); }

	// Link Vertex Attributes
	void linkVertexAttributes(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

	// Get VAO ID
	GLuint getID() { return m_VAOID; }

	// Set VAO ID
	void setID(GLuint ID) { m_VAOID = ID; }


	// ***************************************************
	// Manage Buffers

	// Add Buffer
	


	// Bind/Unbind Buffer


	// Upload Buffer
	void uploadVBO(GLsizeiptr size, const void* data, GLenum usage, size_t VBOIndex);
	void uploadEBO(GLsizeiptr size, const void* data, GLenum usage, size_t EBOIndex);

	// Get Buffer ID



	// Debug only?
	// Get Buffer Type

};

#endif