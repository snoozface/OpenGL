#include "Renderer.h"


void Renderer::linkVertexAttributes(const VertexArray& vao, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	vao.linkVertexAttributes(location, size, type, normalized, stride, offset);
}

size_t Renderer::addShader()
{
	GLuint shaderProgram = glCreateProgram();
	Shader shader(shaderProgram);
	m_shaders.push_back(shader);

	return m_shaders.size() - 1;
}

bool Renderer::createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource, size_t shaderIndex)
{
	if (m_shaders[shaderIndex].createShaderProgram(vertexShaderSource, fragmentShaderSource))
	{
		return true;
	}
	else
		return false;
}

void Renderer::setUniformFloat1(size_t shaderIndex, const std::string& name, float value)
{
	m_shaders[shaderIndex].setUniformFloat1(name, value);
}

void Renderer::setUniformFloat4(size_t shaderIndex, const std::string& name, float value1, float value2, float value3, float value4)
{
	m_shaders[shaderIndex].setUniformFloat4(name, value1, value2, value3, value4);
}

