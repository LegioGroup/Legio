#pragma once

namespace LG 
{
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer 
    {
    public:
        inline static RendererAPI GetRendererAPI() { return s_renderAPI; };
    private:
        static RendererAPI s_renderAPI;
    };
}