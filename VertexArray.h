#ifndef VAO_H
#define VAO_H

#include "Buffer.h"

#include <vector>

class VertexArray
{
private:
	GLuint m_VAOID{};

public:
	VertexArray()
	{
		glGenVertexArrays(1, &m_VAOID);
	}

	// Bind/Unbind VAO
	void bindVAO() { glBindVertexArray(m_VAOID); }
	void unbindVAO() { glBindVertexArray(0); }

	// Link Vertex Attributes
	void linkVertexAttributes(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const;

	// Get VAO ID
	GLuint getID() { return m_VAOID; }

	// Set VAO ID
	void setID(GLuint ID) { m_VAOID = ID; }		// Check this function... why is it here? what is it for?


};

#endif