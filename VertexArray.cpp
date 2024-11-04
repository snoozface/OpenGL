
#include "VertexArray.h"

// Link Vertex Attributes - Currently leaves all VertexAttribArrays Enabled
// Params
// GLuint location - location in vertex shader
// GLint size - seize of vector, vec3 = 3, vec4 = 4 (1, 2, 3, or 4)
// GLenum type - vectors are GL_FLOAT
// GLboolean normalized - if the data is normalized
// GLsizei stride - how far away the next piece of data is (3*sizeof(float) for a one attribute vec3 shader)
// const void* offset - the offset of the data, 0 for the beginning of the buffer
void VertexArray::linkVertexAttributes(GLuint location, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const
{
    glVertexAttribPointer(location, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(location);

}



