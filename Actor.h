#ifndef ACTOR_H
#define ACTOR_H

#include "Shader.h"
#include "VertexArray.h"

class Actor
{
public:
	enum DrawType {
		Arrays,
		Elements
	};
private:
	VertexArray m_VAO{};	// VAO is automatically made for each actor when actor is made
	std::vector<Buffer> m_VBOs{};
	Buffer m_EBO{};
	Shader* m_shader{ nullptr };

	// DrawType used to select DrawArrays or DrawElements
	// Arrays by default, changes to Elements if uploadIndicies() is called
	DrawType m_drawType{ Arrays };		
	std::vector<float> m_vertices{};	// Vertex location data
	std::vector<GLuint> m_indices{};	// Element array indices

	// glBufferData 
	// usage: STREAM, STATIC, or DYNAMIC
	// nature: DRAW, READ, COPY
	// GL_STATIC_DRAW by default, use setter to change
	// usage is used by uploadVBO()
	GLenum m_usage{ GL_STATIC_DRAW };

public:
	Actor()
	{}

	// ***************************************************
	// Data Management

	// Upload Vertices
	void uploadVertices(std::vector<float> vertices) { m_vertices = vertices; }

	// Upload Indices
	// Sets m_drawType to Elements which causes drawElements to be used instead of drawArrays
	void uploadIndices(std::vector<GLuint> indices);

	// Connect to Shader
	void connectShader(Shader* shader) { m_shader = shader; }

	// Upload data to Uniform, This is a function for chapter 6.4 uniforms only!
	// Delete if this program ever becomes a thing
	void uploadUniform();

	// ***************************************************
	// Render

	void render(GLenum mode);

private:
	// drawArrays is called by render() if data was not sent to m_indicies with uploadIndicies()
	void drawArrays(GLenum mode);

	// drawElements is called by render() if data was sent to m_indicies with uploadIndicies()
	void drawElements(GLenum mode);

public:
	// ***************************************************
	// VAO

	// Bind/Unbind VAO
	void bindVAO() { m_VAO.bindVAO(); }
	void unbindVAO() { m_VAO.unbindVAO(); }

	// Link Vertex Attributes
	void linkVertexAttributes(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

	// Get VAO ID
	GLuint getVAO() { return m_VAO.getID(); }

	// ***************************************************
	// Buffers

	// ***************************************************
	// VBO

	// Add VBO
	size_t addVBO();

	// Bind/Unbind VBO
	void bindVBO(size_t VBOIndex) { m_VBOs[VBOIndex].bindBuffer(); }
	void unbindVBO(size_t VBOIndex) { m_VBOs[VBOIndex].unbindBuffer(); }

	// Upload Buffer
	//void uploadVBO(size_t VBOIndex, GLsizeiptr size, const void* data, GLenum usage);
	//void uploadVBO(size_t VBOIndex, std::vector<float>& vertices);
	template <typename T>
	void uploadVBO(size_t VBOIndex, std::vector<T>& vector)
	{
		m_VBOs[VBOIndex].uploadBuffer(vector, m_usage);
	}

	// Get VBO ID
	GLuint getVBOID(size_t VBOIndex) { return m_VBOs[VBOIndex].getID(); }


	// ***************************************************
	// EBO

	// Add EBO
	void addEBO() { m_EBO = { Buffer::Type::EBO }; }

	// Bind/Unbind EBO
	void bindEBO() { m_EBO.bindBuffer(); }
	void unbindEBO() { m_EBO.unbindBuffer(); }

	// Upload Buffer
	// usage is set by m_usage
	//void uploadEBO(GLsizeiptr size, const void* data, GLenum usage);
	template <typename T>
	void uploadEBO(std::vector<T>& vector)
	{
		m_EBO.uploadBuffer(vector, m_usage);
	}

	// Get EBO ID
	GLuint getEBOID() { return m_EBO.getID(); }

	// ***************************************************
	// glBufferData
	GLenum getUsage() { return m_usage; }
	void setUsage(GLenum usage) { m_usage = usage; }





	// Debug only?
	// Get Buffer Type
	std::string getVBOType(size_t VBOIndex) { return m_VBOs[VBOIndex].getType(); }
	std::string getEBOType() { return m_EBO.getType(); }

};

#endif