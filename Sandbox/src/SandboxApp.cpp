#include <Legio.h>

class ExampleLayer : public LG::Layer
{
public:
  ExampleLayer()
    :Layer("Example") {}

  virtual void OnUpdate() override
  {
    LG_INFO("ExampleLayer::Update");
  }

  virtual void OnEvent(LG::Event& event) override
  {
    LG_TRACE("{0}", event);
  }
};

class SandboxApp : public LG::Application
{
public:
  SandboxApp()
  {
    PushLayer(new ExampleLayer());
  };
  ~SandboxApp()
  {
  };
};

LG::Application* LG::CreateApplication()
{
  return new SandboxApp();
}
