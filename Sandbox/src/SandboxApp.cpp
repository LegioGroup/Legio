#include <Legio.h>

class ExampleLayer : public LG::Layer
{
public:
    ExampleLayer()
        :Layer("Example") {}

    virtual void OnUpdate() override
    {
        if (LG::Input::IsKeyPressed(LG_KEY_TAB))
            LG_INFO("Tab Key is pressed");
    }

    virtual void OnEvent(LG::Event& event) override
    {
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
