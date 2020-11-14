#pragma once
#include "LGCore.h"
#include "Window.h"
#include <Legio/Events/ApplicationEvent.h>


namespace LG{

  class LG_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    bool OnWindowClosed(WindowCloseEvent& e);
  private:
    std::unique_ptr<Window> m_Window;
    bool m_running = true;

  };

  Application* CreateApplication();

}

