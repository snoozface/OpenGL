#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <type_traits>		// for std::is_same_v
#include <vector>


class Buffer
{
public:
	enum Type
	{
		EBO,
		VBOPos,
		VBOColor,
		VBOTexCoord,
		MaxBuffers
	};
protected:
	GLuint m_ID{};
	Type m_type{};

public:
	Buffer(Type type)
		: m_type{ type }
	{
		glGenBuffers(1, &m_ID);
	}


	GLuint getID() const { return m_ID; }
	Type getType() const { return m_type; }

	// Bind/Unbind Buffer
	void bindBuffer();
	void unbindBuffer();


	/*
	* uploadBuffer
	* 
	* Param std::vector<T> data for EBO or VBO data
	* 
	* If data is vector<int>, function calls EBO::uploadIntData() and uploads to the EBO
	* If data is vector<float>, function calls VBO::uploadFloatData() and uploads to the VBO
	* 
	* uploadBuffer definition is in BufferTemplate.cpp
	*/
public:
	template <typename T>
	void uploadBuffer(const std::vector<T>& data, GLenum usage);
private:
	virtual void uploadIntData(const std::vector<int>& data, GLenum usage) {}
	virtual void uploadFloatData(const std::vector<float>& data, GLenum usage) {}


	// Debug function - getType
	// Returns std::string_view of Buffer Type
	std::string_view getTypeName() const;
};

#include "BufferTemplate.cpp"


#endif