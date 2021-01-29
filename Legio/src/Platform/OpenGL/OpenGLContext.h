#pragma once
#include "Legio/Renderer/GraphicsContext.h"


struct GLFWwindow;
namespace LG 
{
    class OpenGLContext : public GraphicsContext 
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_windowHandle;
    };
}