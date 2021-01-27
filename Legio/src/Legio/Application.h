#pragma once
#include "LGCore.h"

#include "Window.h"
#include "Legio/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Legio/ImGui/ImGuiLayer.h"

namespace LG {

    class LG_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() const { return *m_Window; }

    private:
        bool OnWindowClosed(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}

