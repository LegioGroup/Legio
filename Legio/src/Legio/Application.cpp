#include "lgpch.h"
#include "Application.h"

#include <glad/glad.h>

namespace LG
{
    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type) 
    {
        switch (type)
        {
        case LG::ShaderDataType::Float:
        case LG::ShaderDataType::Float2:
        case LG::ShaderDataType::Float3:
        case LG::ShaderDataType::Float4:
        case LG::ShaderDataType::Mat3:
        case LG::ShaderDataType::Mat4:  return GL_FLOAT;
        case LG::ShaderDataType::Int:
        case LG::ShaderDataType::Int2:
        case LG::ShaderDataType::Int3:
        case LG::ShaderDataType::Int4:  return GL_INT;
        case LG::ShaderDataType::Bool:  return GL_BOOL;
        }
    }

    Application::Application()
    {
        LG_CORE_ASSERT(!s_Instance, "Application already exist!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(LG_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.4f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.2f, 0.3f, 1.0f
        };

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout= 
        {
            {ShaderDataType::Float3, "a_Positon"},
            {ShaderDataType::Float4, "a_Color"},
        };
        m_vertexBuffer->SetLayout(layout);

        uint32_t index = 0;
        for (const auto& element : m_vertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGlBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*) element.Offset);
            index++;
        }


        unsigned int indices[3] = {0, 1, 2};
        m_indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_indexBuffer->Bind();

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            out vec3 v_Position;
            out vec4 v_Color;
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {

        while (m_Running)
        {
            glClearColor(0.2f, 0.2f, 0.2f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(LG_BIND_EVENT_FN(Application::OnWindowClosed));

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