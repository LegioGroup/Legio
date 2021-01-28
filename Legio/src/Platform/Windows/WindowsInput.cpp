#include "lgpch.h"
#include "WindowsInput.h"

#include "Legio/Application.h"
#include <GLFW/glfw3.h>
namespace LG
{
    Input* Input::s_instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keyCode)
    {
        const auto& window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        int state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        const auto& window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        const auto& window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto [xPos, yPos] = GetMousePositionImpl();
        return xPos;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto [xPos, yPos] = GetMousePositionImpl();
        return yPos;
    }

}