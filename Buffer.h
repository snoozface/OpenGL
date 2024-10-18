#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <vector>

class Buffer
{
public:
	enum Type
	{
		VBO,
		EBO
	};
private:
	GLuint m_bufferID{};
	Type m_type{};

public:
	Buffer()
	{}

	Buffer(Type type)
		: m_type{ type }
	{
		glGenBuffers(1, &m_bufferID);
	}

	// Bind/Unbind Buffer
	void bindBuffer();
	void unbindBuffer();

	// Upload Buffer Data
	//void uploadBuffer(GLsizeiptr size, const void* data, GLenum usage);
	//template <typename T>
	//void uploadBuffer(std::vector<T> &vector, GLenum usage);

	template <typename T>
	void uploadBuffer(std::vector<T>& vector, GLenum usage)
	{
		switch (m_type)
		{
		case Type::VBO:
			glBufferData(GL_ARRAY_BUFFER, vector.size() * sizeof(T), vector.data(), usage);
			break;
		case Type::EBO:
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, vector.size() * sizeof(T), vector.data(), usage);
			break;

		default:
			std::cerr << "ERROR: Buffer::uploadBuffer() Attempted to upload to buffer with incorrect type\n";
			break;
		}
	}

	// Get Buffer ID
	GLuint getID() { return m_bufferID; }





	// Debug only?
	// Get Buffer Type
	std::string getType()
	{
		switch (m_type)
		{
		case Type::VBO:
			return "VBO";
		case Type::EBO:
			return "EBO";
		default:
			return "ERROR::INCORECT TYPE";
		}
	}
};

#endif