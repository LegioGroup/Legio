#pragma once
#include "Legio/Layer.h"

namespace LG {

    class LG_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0;
    };
}