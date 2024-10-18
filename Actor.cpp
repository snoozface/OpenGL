#include "Actor.h"

#include <cmath>

void Actor::uploadIndices(std::vector<GLuint> indices)
{
	m_indices = indices;
	m_drawType = Elements;
}

/*
* This is a function for chapter 6.4 uniforms only
* 
* to use it, make sure the 6.4 shaders are being used and call it from render() like so:
* 
* 	m_shader->useShaderProgram();

	uploadUniform();

	switch (m_drawType)
*/
void Actor::uploadUniform()
{
	float timeValue = static_cast<float>(glfwGetTime());
	float greenValue = sin(2 * timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(m_shader->getShaderID(), "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

void Actor::render(GLenum mode)
{
	m_VAO.bindVAO();
	m_shader->useShaderProgram();

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
}

void Actor::drawArrays(GLenum mode)
{
	glDrawArrays(mode, 0, static_cast<GLsizei>(m_vertices.size()) * sizeof(float));
}

void Actor::drawElements(GLenum mode)
{
	glDrawElements(mode, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
}

void Actor::linkVertexAttributes(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	m_VAO.linkVertexAttributes(location, size, type, normalized, stride, offset);
}

size_t Actor::addVBO()
{
	Buffer VBO{ Buffer::Type::VBO };
	m_VBOs.push_back(VBO);

	return m_VBOs.size() - 1;
}


