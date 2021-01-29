#include "lgpch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace LG 
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        LG_CORE_ASSERT(windowHandle, "Window handle is Null!")
    }
    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LG_CORE_ASSERT(status, "Failed to initialize Glad!");

        LG_CORE_INFO("OpenGL Info:");
        LG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR))
        LG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER))
        LG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION))
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}