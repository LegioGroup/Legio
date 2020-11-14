#pragma once
#include "LGCore.h"
#include "Window.h"

namespace LG{

  class LG_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  private:
    std::unique_ptr<Window> m_Window;
    bool m_running = true;

  };

  Application* CreateApplication();

}

