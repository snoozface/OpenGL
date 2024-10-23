#include "Buffer.h"

void Buffer::bindBuffer()
{
	switch (m_type)
	{
	case Type::VBO:
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		break;
	case Type::EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		break;

	default:
		std::cerr << "ERROR: Buffer::bindBuffer() Attempted to bind buffer with incorrect type\n";
		break;
	}
}

void Buffer::unbindBuffer()
{
	switch (m_type)
	{
	case Type::VBO:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;
	case Type::EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		break;

	default:
		std::cerr << "ERROR: Buffer::unbindBuffer() Attempted to unbind buffer with incorrect type\n";
		break;
	}
}

