#pragma once
#include "Legio/LGCore.h"
namespace LG 
{
    class LG_API Input 
    {
    public:
        inline static bool IsKeyPressed(int key) { return s_instance->IsKeyPressedImpl(key); }

        inline static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_instance->GetMouseXImpl(); }
        inline static float GetMouseY() { return s_instance->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(int keyCode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
    private:
        static Input* s_instance;
    };
}
