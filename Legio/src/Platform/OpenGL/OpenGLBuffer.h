#pragma once
#include "Legio/Renderer/Buffer.h"

namespace LG 
{
    class OpenGlVertexBuffer : public VertexBuffer 
    {
    public:
        OpenGlVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGlVertexBuffer() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void inline SetLayout(const BufferLayout& layout) override { m_layout = layout; };
        virtual const inline BufferLayout& GetLayout() override { return m_layout; };
    private:
        uint32_t m_programID;
        BufferLayout m_layout;
    };

    class OpenGlIndexBuffer : public IndexBuffer
    {
    public:
        OpenGlIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGlIndexBuffer() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual uint32_t getCount() const override;

    private:
        uint32_t m_programID;
        uint32_t m_count;
    };
}