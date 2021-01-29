#pragma once
#include "LGCore.h"

#include "Window.h"
#include "Legio/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Legio/ImGui/ImGuiLayer.h"
#include "Legio/Renderer/Shader.h"

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
        std::unique_ptr<Shader> m_Shader;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        unsigned int m_vertexArray;
        unsigned int m_vertexBuffer;
        unsigned int m_indexBuffer;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();

}

