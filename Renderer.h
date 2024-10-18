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
	void uploadVertices(Actor& actor, std::vector<float> vertices) { actor.uploadVertices(vertices); }

	// Upload Indices to Actor vector of indicies
	// Move this function after Actor gets an unordered map, should be from Game not Renderer
	void uploadIndices(Actor& actor, std::vector<GLuint> indices) { actor.uploadIndices(indices); }

	// Connect Shader
	// Move this function after Actor gets an unordered map, should be from Game not Renderer
	void connectShader(Actor& actor, size_t shaderIndex) { actor.connectShader(&m_shaders[shaderIndex]); }

	// Actor Data Upload Functions
	// ***************************************************





	// ***************************************************
	// VAO

	// Bind/Unbind 
	void bindVAO(Actor& actor) { actor.bindVAO(); }
	void unbindVAO(Actor& actor) { actor.unbindVAO(); }

	// Link Vertex Attributes
	void linkVertexAttributes(Actor& actor, GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

	// Get VAO from Actor
	GLuint getVAO(Actor& actor) { return actor.getVAO(); }

	// ***************************************************
	// Buffers

	// ***************************************************
	// Buffers - VBO

	// Add VBO
	size_t addVBO(Actor& actor) { return actor.addVBO(); }

	// Bind/Unbind VBO
	void bindVBO(Actor& actor, size_t VBOIndex) { actor.bindVBO(VBOIndex); }
	void unbindVBO(Actor& actor, size_t VBOIndex) { actor.unbindVBO(VBOIndex); }

	// Upload VBO
	//void uploadVBO(size_t actorIndex, size_t VBOIndex, GLsizeiptr size, const void* data, GLenum usage);
	//void uploadVBO(size_t actorIndex, size_t VBOIndex, std::vector<float>& vertices);
	template <typename T>
	void uploadVBO(Actor& actor, size_t VBOIndex, std::vector<T>& vector)
	{
		actor.uploadVBO(VBOIndex, vector);
	}

	// Get VBO ID
	GLuint getVBO(Actor& actor, size_t VBOIndex) { return actor.getVBOID(VBOIndex); }

	// ***************************************************
	// Buffers - EBO

	// Add EBO
	void addEBO(Actor& actor) { actor.addEBO(); }

	// Bind/Unbind EBO
	void bindEBO(Actor& actor) { actor.bindEBO(); }
	void unbindEBO(Actor& actor) { actor.unbindEBO(); }

	// Upload EBO
	//void uploadEBO(size_t actorIndex, GLsizeiptr size, const void* data, GLenum usage);
	template <typename T>
	void uploadEBO(Actor& actor, std::vector<T>& vector)
	{
		actor.uploadEBO(vector);
	}

	// Get EBO ID
	GLuint getEBO(Actor& actor) { return actor.getEBOID(); }


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
	std::string getVBOType(Actor& actor, size_t VBOIndex) { return actor.getVBOType(VBOIndex); }
	std::string getEBOType(Actor& actor) { return actor.getEBOType(); }
};

#endif