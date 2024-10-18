#include "Buffer.h"

void Buffer::bindBuffer()
{
	switch (m_type)
	{
	case Type::VBO:
		std::cout << "bound VBO\n";
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		break;
	case Type::EBO:
		std::cout << "bound EBO\n";
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

//void Buffer::uploadBuffer(GLsizeiptr size, const void* data, GLenum usage)
//{
//	switch (m_type)
//	{
//	case Type::VBO:
//		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
//		break;
//	case Type::EBO:
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
//		break;
//
//	default:
//		std::cerr << "ERROR: Buffer::uploadBuffer() Attempted to upload to buffer with incorrect type\n";
//		break;
//	}
//}

//template <typename T>
//void Buffer::uploadBuffer(std::vector<T>& vector, GLenum usage)
//{
//	switch (m_type)
//	{
//	case Type::VBO:
//		glBufferData(GL_ARRAY_BUFFER, vector.size() * sizeof(vector[0]), vector.data(), usage);
//		break;
//	case Type::EBO:
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector.size() * sizeof(vector[0]), vector.data(), usage);
//		break;
//
//	default:
//		std::cerr << "ERROR: Buffer::uploadBuffer() Attempted to upload to buffer with incorrect type\n";
//		break;
//	}
//}
