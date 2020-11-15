#pragma once
#include "LGCore.h"
#include "Window.h"
#include "Legio/LayerStack.h"
#include <Legio/Events/ApplicationEvent.h>


namespace LG{

  class LG_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

  private:
    bool OnWindowClosed(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;

  };

  Application* CreateApplication();

}

