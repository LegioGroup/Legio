#include "lgpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace LG 
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetRendererAPI())
        {
        case RendererAPI::None:
            LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGlVertexBuffer(vertices, size);
        }
        LG_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetRendererAPI())
        {
        case RendererAPI::None:
            LG_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGlIndexBuffer(indices, count);
        }
        LG_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}