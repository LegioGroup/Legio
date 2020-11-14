#include "lgpch.h"
#include "Application.h"

#include <Legio/Events/ApplicationEvent.h>
#include <GLFW/glfw3.h>

namespace LG
{

  Application::Application()
  {
    m_Window = std::unique_ptr<Window>(Window::Create());
  }

  Application::~Application()
  {

  }

  void Application::Run()
  {

    while (m_running) 
    {
      glClearColor(1, 0.5f, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      m_Window->OnUpdate();
    }
  }
}