#include <Legio.h>


class SandboxApp : public LG::Application
{
public:
  SandboxApp()
  {
    PushOverlay(new LG::ImGuiLayer());
  };
  ~SandboxApp()
  {
  };
};

LG::Application* LG::CreateApplication()
{
  return new SandboxApp();
}
