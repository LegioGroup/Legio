#include "lgpch.h"

#include "WindowsWindow.h"
#include "Legio/Log.h"
#include <Legio/Events/ApplicationEvent.h>
#include <Legio/Events/MouseEvent.h>
#include <Legio/Events/KeyEvent.h>

namespace LG {
  static bool s_GLFWInitialized = false;

  static void GLFWErrorCallback(int error, const char* description) 
  {
    LG_CORE_ERROR("GLFW Error ({0}): {1}",error, description);
  }

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
      glfwSetErrorCallback(GLFWErrorCallback);
      s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    //Set GLFW callbacks

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
      });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.EventCallback(event);
      });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
          case GLFW_PRESS:
          {
            KeyPressedEvent event(key, 0);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE:
          {
            KeyReleasedEvent event(key);
            data.EventCallback(event);
            break;
          }
          case GLFW_REPEAT:
          {
            KeyPressedEvent event(key, 1);
            data.EventCallback(event);
            break;
          }
        }
      });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        
        switch (action)
        {
          case GLFW_PRESS:
          {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE: 
          {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
          }
        }
      });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        data.EventCallback(event);
      });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
      {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));
        data.EventCallback(event);
      });



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