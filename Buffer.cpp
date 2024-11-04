#include "Buffer.h"



void checkError()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "Error binding buffer: " << error << std::endl;
	}
}

void Buffer::bindBuffer()
{
	switch (m_type)
	{
	case Type::EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		checkError();
		break;
	case Type::VBOPos:
	case Type::VBOColor:
	case Type::VBOTexCoord:
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		checkError();
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
	case Type::EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		break;
	case Type::VBOPos:
	case Type::VBOColor:
	case Type::VBOTexCoord:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	default:
		std::cerr << "ERROR: Buffer::unbindBuffer() Attempted to unbind buffer with incorrect type\n";
		break;
	}
}


// Debug function - getType
// Returns std::string_view of Buffer Type
std::string_view Buffer::getTypeName() const
{
	switch (m_type)
	{
	case EBO:
		return "EBO";
	case VBOPos:
		return "VBOPos";
	case VBOColor:
		return "VBOColor";
	case VBOTexCoord:
		return "VBOTexCoord";
	default:
		std::cerr << "ERROR Buffer::getType() called with invalid Type\n";
		return "oops Buffer::getType() called with invalid Type";
	}
}




