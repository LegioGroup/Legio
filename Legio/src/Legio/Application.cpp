#include "lgpch.h"
#include "Application.h"

#include <Legio/Events/ApplicationEvent.h>
#include "Legio/Log.h"

namespace LG
{

  Application::Application()
  {

  }

  Application::~Application()
  {

  }

  void Application::Run()
  {
    WindowResizeEvent e(1280, 720);
    LG_TRACE(e);
    while (true);
  }
}