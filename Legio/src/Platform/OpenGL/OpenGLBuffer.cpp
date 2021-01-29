#include "lgpch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"
namespace LG
{
    //----------------VERTEX BUFFER------------------------

    OpenGlVertexBuffer::OpenGlVertexBuffer(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &m_programID);
        glBindBuffer(GL_ARRAY_BUFFER, m_programID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer()
    {
        glDeleteBuffers(1, &m_programID);
    }

    void OpenGlVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_programID);
    }

    void OpenGlVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //----------------INDEX BUFFER------------------------

    OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t* indices, uint32_t count)
        : m_count(count)
    {
        glCreateBuffers(1, &m_programID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_programID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer()
    {
        glDeleteBuffers(1, &m_programID);
    }

    void OpenGlIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_programID);
    }

    void OpenGlIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGlIndexBuffer::getCount() const
    {
        return m_count;
    }

}