#include "lgpch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"
namespace LG
{
    Application* Application::s_Instance = nullptr;


    Application::Application()
    {
        LG_CORE_ASSERT(!s_Instance, "Application already exist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(LG_BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

        while (m_Running)
        {

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            auto [x, y] = Input::GetMousePosition();
            //LG_CORE_TRACE("{0}, {1}", x, y);
            m_Window->OnUpdate();
            glClearColor(1, 0.5f, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LG_BIND_EVENT_FN(Application::OnWindowClosed));

        //LG_CORE_TRACE("{0}", e);

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
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}