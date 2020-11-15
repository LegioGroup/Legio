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
    virtual void OnUpdate() override;
    virtual void OnEvent(Event& event) override;

  private:
    float m_Time = 0;
  };
}