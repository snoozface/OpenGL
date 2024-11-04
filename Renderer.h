#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
private:
	// Vector of Shaders
	// Program object manages shader objects, each Actor has a pointer 
	// to a shader that it uses
	std::vector<Shader> m_shaders{};

public:
	Renderer()
	{}


	// Link Vertex Attributes
	//void linkVertexAttributes(const std::shared_ptr<Actor>& actor, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);
	void linkVertexAttributes(const VertexArray& vao, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);


	// ***************************************************
	// Shaders

	// Add Shader
	size_t addShader();

	// Create Shader Program
	bool createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource, size_t shaderIndex);

	// Use/Unuse Shader Program
	void useShaderProgram(size_t shaderIndex) { m_shaders[shaderIndex].useShaderProgram(); }
	void unuseShaderProgram(size_t shaderIndex) { m_shaders[shaderIndex].unuseShaderProgram(); }

	// Get Shader ID
	GLuint getShaderID(size_t shaderIndex) { return m_shaders[shaderIndex].getShaderID(); }

	// Get Shader Reference
	Shader& getShader(size_t shaderIndex) { return m_shaders[shaderIndex]; }


	// ***************************************************
	// Uniform Functions
	
	// Uniform setters
	void setUniformFloat1(size_t shaderIndex, const std::string& name, float value);
	void setUniformFloat4(size_t shaderIndex, const std::string& name, float value1, float value2, float value3, float value4);


};

#endif