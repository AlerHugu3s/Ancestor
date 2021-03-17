#include "acpch.h"
#include "WindowsInput.h"

#include "Ancestor/Application.h"
#include <GLFW/glfw3.h>


namespace Ancestor {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());		
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos,(float)yPos };
	}
	float WindowsInput::GetMousePosXImpl()
	{
		auto [x, y] = GetMousePosition();
		return x;
	}
	float WindowsInput::GetMousePosYImpl()
	{
		auto [x, y] = GetMousePosition();
		return y;
	}
}