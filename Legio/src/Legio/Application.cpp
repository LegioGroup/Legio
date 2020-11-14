#include "lgpch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

namespace LG
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

  Application::Application()
  {
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

    LG_CORE_TRACE("{0}",e);
  }

  bool Application::OnWindowClosed(WindowCloseEvent& e)
  {
    m_running = false;
    return true;
  }
}