#ifndef RENDERER_H
#define RENDERER_H

#include "Actor.h"

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

	// ***************************************************
	// Actor Data Upload Functions
	// Move these functions to Game instead of Renderer
	// Once Game gets unordered map of std::shared_ptr<Actor> instead of vector

	// Upload Vertices to Actor vector of vertices
	// Move this function after Actor gets an unordered map, should be from Game not Renderer
	void uploadVertices(const std::shared_ptr<Actor>& actor, std::vector<float> vertices) { actor->uploadVertices(vertices); }

	// Upload Indices to Actor vector of indicies
	// Move this function after Actor gets an unordered map, should be from Game not Renderer
	void uploadIndices(const std::shared_ptr<Actor>& actor, std::vector<GLuint> indices) { actor->uploadIndices(indices); }

	// Connect Shader
	// Move this function after Actor gets an unordered map, should be from Game not Renderer
	void connectShader(const std::shared_ptr<Actor>& actor, size_t shaderIndex) { actor->connectShader(&m_shaders[shaderIndex]); }

	// Actor Data Upload Functions
	// ***************************************************





	// ***************************************************
	// VAO

	// Bind/Unbind 
	void bindVAO(const std::shared_ptr<Actor>& actor) { actor->bindVAO(); }
	void unbindVAO(const std::shared_ptr<Actor>& actor) { actor->unbindVAO(); }		// Currently unused function

	// Link Vertex Attributes
	void linkVertexAttributes(const std::shared_ptr<Actor>& actor, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

	// Get VAO from Actor
	GLuint getVAO(const std::shared_ptr<Actor>& actor) { return actor->getVAO(); }	// Currenlty unused function

	// ***************************************************
	// Buffers

	// ***************************************************
	// Buffers - VBO

	// Add VBO
	size_t addVBO(const std::shared_ptr<Actor>& actor) { return actor->addVBO(); }

	// Bind/Unbind VBO
	void bindVBO(const std::shared_ptr<Actor>& actor, size_t VBOIndex) { actor->bindVBO(VBOIndex); }
	void unbindVBO(const std::shared_ptr<Actor>& actor, size_t VBOIndex) { actor->unbindVBO(VBOIndex); }	// Currently unused function

	// Upload VBO
	//void uploadVBO(size_t actorIndex, size_t VBOIndex, GLsizeiptr size, const void* data, GLenum usage);
	//void uploadVBO(size_t actorIndex, size_t VBOIndex, std::vector<float>& vertices);
	template <typename T>
	void uploadVBO(const std::shared_ptr<Actor>& actor, size_t VBOIndex, std::vector<T>& vector)
	{
		actor->uploadVBO(VBOIndex, vector);
	}

	// Get VBO ID
	GLuint getVBO(const std::shared_ptr<Actor>& actor, size_t VBOIndex) { return actor->getVBOID(VBOIndex); }	// Currently unused function

	// ***************************************************
	// Buffers - EBO

	// Add EBO
	void addEBO(const std::shared_ptr<Actor>& actor) { actor->addEBO(); }

	// Bind/Unbind EBO
	void bindEBO(const std::shared_ptr<Actor>& actor) { actor->bindEBO(); }
	void unbindEBO(const std::shared_ptr<Actor>& actor) { actor->unbindEBO(); }		// Currently unused function

	// Upload EBO
	//void uploadEBO(size_t actorIndex, GLsizeiptr size, const void* data, GLenum usage);
	template <typename T>
	void uploadEBO(const std::shared_ptr<Actor>& actor, std::vector<T>& vector)
	{
		actor->uploadEBO(vector);
	}

	// Get EBO ID
	GLuint getEBO(const std::shared_ptr<Actor>& actor) { return actor->getEBOID(); }	// Currently unused function


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



	// ***************************************************
	// Render Options

	// Wireframe mode
	// Call with True/False to set wireframe mode On/Off
	// Globally based on context
	void setWireframe(bool wire);





	// Debug only?
	// Get Buffer Type
	std::string getVBOType(const std::shared_ptr<Actor>& actor, size_t VBOIndex) { return actor->getVBOType(VBOIndex); }	// Currently unused function
	std::string getEBOType(const std::shared_ptr<Actor>& actor) { return actor->getEBOType(); }		// Currently unused function
};

#endif