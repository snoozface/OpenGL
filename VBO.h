#ifndef VBO_H
#define VBO_H

#include "Buffer.h"
class VBO :
    public Buffer
{
public:
	VBO(Buffer::Type type)
		: Buffer(type)
	{}


private:
	void uploadFloatData(const std::vector<float>& data, GLenum usage) override
	{
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
	}

};

#endif