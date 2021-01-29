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
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
}