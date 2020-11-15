#include "lgpch.h"
#include "Application.h"

#include <glad/glad.h>

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

    while (m_Running) 
    {
      glClearColor(1, 0.5f, 0, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      m_Window->OnUpdate();

      for (Layer* layer : m_LayerStack) 
      {
        layer->OnUpdate();
      }
    }
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

    LG_CORE_TRACE("{0}",e);
  
    //Events are handled in revers ordered since the end of the layer is what is gonna be rendered last.
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) 
    {
      (*--it)->OnEvent(e);
      if (e.Handled())
        break;
    }
  }

  void Application::PushLayer(Layer* layer)
  {
    m_LayerStack.PushLayer(layer);
  }

  void Application::PushOverlay(Layer* overlay)
  {
    m_LayerStack.PushOverlay(overlay);
  }

  bool Application::OnWindowClosed(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }
}