#include "lgpch.h"

#include "WindowsWindow.h"
#include "Legio/Log.h"

namespace LG {
  static bool s_GLFWInitialized = false;

  Window* Window::Create(const WindowProps& props)
  {
    return new WindowsWindow(props);
  }

  LG::WindowsWindow::WindowsWindow(const WindowProps& props)
  {
    Init(props);
  }

  LG::WindowsWindow::~WindowsWindow()
  {
    Shutdown();
  }

  void LG::WindowsWindow::Init(const WindowProps& props)
  {
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
    
    LG_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

    if (!s_GLFWInitialized) 
    {
      int success = glfwInit();
      LG_CORE_ASSERT(success, "Could not initialize GLFW!")
      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
  }

  void LG::WindowsWindow::Shutdown()
  {
    glfwDestroyWindow(m_Window);
  }
  void LG::WindowsWindow::OnUpdate()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }

  void LG::WindowsWindow::SetVSync(bool enabled)
  {
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    m_Data.VSync = enabled;
  }

  bool LG::WindowsWindow::IsVSync() const
  {
    return m_Data.VSync;
  }


}