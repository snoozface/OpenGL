#pragma once
#include "Buffer.h"
class EBO :
    public Buffer
{
private:
    std::vector<int> m_data{};

public:
    EBO(Buffer::Type type)
        : Buffer(type)
    {}


    const std::vector<int>& getData() const { return m_data; }

private:
    void uploadIntData(const std::vector<int>& data, GLenum usage) override
    {
        m_data = data;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), usage);
    }

};

