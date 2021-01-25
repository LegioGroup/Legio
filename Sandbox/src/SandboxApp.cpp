#include <Legio.h>

class ExampleLayer : public LG::Layer
{
public:
    ExampleLayer()
        :Layer("Example") {}

    virtual void OnUpdate() override
    {
        //G_INFO("ExampleLayer::Update");
        if (LG::Input::IsKeyPressed(LG_KEY_TAB))
            LG_INFO("Tab Key is pressed");
    }

    virtual void OnEvent(LG::Event& event) override
    {
       // LG_TRACE("{0}", event);
    }
};

class SandboxApp : public LG::Application
{
public:
    SandboxApp()
    {
        PushLayer(new ExampleLayer());
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
