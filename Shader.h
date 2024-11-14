#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glfw3.h>

#include <fstream>

class Shader
{
private:
	GLuint m_shaderProgram{};
	GLuint m_vertexShader{};
	GLuint m_fragmentShader{};

	char* m_shaderSourceString{};

public:
	Shader(GLuint shaderProgram)
		: m_shaderProgram{ shaderProgram }
	{}


	GLuint getShaderID() { return m_shaderProgram; }

	bool createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource);

	void useShaderProgram() { glUseProgram(m_shaderProgram); }
	void unuseShaderProgram() { glUseProgram(0); }

	// ***************************************************
	// Uniform Functions

	// Uniform setters
	void setUniformInt1(const std::string& name, int value);
	void setUniformFloat1(const std::string& name, float value);
	void setUniformFloat4(const std::string& name, float value1, float value2, float value3, float value4);


private:
	bool createVertexShader(std::string shaderFile);
	bool createFragmentShader(std::string shaderFile);
	char* readShaderFile(std::string shaderFile);
};

#endif