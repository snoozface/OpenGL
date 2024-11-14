#include "Shader.h"

#include <iostream>
#include <string>

bool Shader::createShaderProgram(std::string vertexShaderSource, std::string fragmentShaderSource)
{
	// Create vertex shader, attach source code, and compile
	createVertexShader(vertexShaderSource);

	// Create fragment shader, attach source code, and compile
	createFragmentShader(fragmentShaderSource);

	// Attach and link shaders into shader program
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragmentShader);
	glLinkProgram(m_shaderProgram);

	// Test if link was successful
	GLint success{};
	char infoLog[512];
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION::FAILED\n"
			<< infoLog << '\n';
		return false;
	}

	// Delete vertex and fragment shaders
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);

    return true;
}

void Shader::setUniformInt1(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void Shader::setUniformFloat1(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}

void Shader::setUniformFloat4(const std::string& name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_shaderProgram, name.c_str()), value1, value2, value3, value4);
}

bool Shader::createVertexShader(std::string shaderFile)
{
	// Read Shader File
	const char* shaderSourceString = readShaderFile(shaderFile);

	// Create vertex shader, attach source code, and compile
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShader, 1, &shaderSourceString, nullptr);
	glCompileShader(m_vertexShader);
	// Test if compiliation was successful
	GLint success{};
	char infoLog[512];
	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_vertexShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n"
			<< infoLog << '\n';
		return false;
	}

	return true;
}

bool Shader::createFragmentShader(std::string shaderFile)
{
	// Read Shader File
	const char* shaderSourceString = readShaderFile(shaderFile);

	// Create vertex shader, attach source code, and compile
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShader, 1, &shaderSourceString, nullptr);
	glCompileShader(m_fragmentShader);
	// Test if compiliation was successful
	GLint success{};
	char infoLog[512];
	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_fragmentShader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n"
			<< infoLog << '\n';
		return false;
	}

	return true;
}

char* Shader::readShaderFile(std::string shaderFile)
{
	// My way of reading the files...
	// works but you need to make a few variables and convert types before returning


	//// Copy shader source file into ifstream
	//std::ifstream shaderSourceStream{ shaderFile };
	//// Test if file was found (some data will be in ifstream)
	//if (!shaderSourceStream)
	//{
	//	std::cerr << "ERROR: Shader::createShader() No data in ifstream, potential file name error.\n";
	//}
	//// Transfer data to string
	//std::string shaderSourceString((std::istreambuf_iterator<char>(shaderSourceStream)),
	//	std::istreambuf_iterator<char>());


	//const char* shaderSourceConst = shaderSourceString.c_str();
	//char* shaderSourceNonConst = _strdup(shaderSourceConst);

	//return shaderSourceNonConst;

	// copilots way
	// seems better but i don't fully understand it


	// Open the file
	std::ifstream shaderSourceStream(shaderFile, std::ios::in | std::ios::binary | std::ios::ate);
	if (!shaderSourceStream)
	{
		std::cerr << "ERROR: Shader::createShader() No data in ifstream, potential file name error.\n";
		return nullptr;
	}

	// Get the size of the file
	std::streamsize size = shaderSourceStream.tellg();
	shaderSourceStream.seekg(0, std::ios::beg);

	// Allocate memory for the file content
	char* buffer = new char[size + 1];
	if (shaderSourceStream.read(buffer, size))
	{
		buffer[size] = '\0'; // Null-terminate the string
		return buffer;
	}
	else
	{
		delete[] buffer;
		std::cerr << "ERROR: Shader::createShader() Failed to read the file.\n";
		return nullptr;
	}
}
