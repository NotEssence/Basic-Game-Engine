#include "bgepch.h"

#include "Platform/Windows/WindowsInput.h"
#include "Bge/Logger.h"
#include "Bge/Application.h"

#include <GLFW/glfw3.h>

namespace Bge
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyReleasedImpl(KeyCode keycode)
	{
		BGE_SET_TRACE;

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);

		BGE_REMOVE_TRACE;

		return state == GLFW_RELEASE;

	}

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode)
	{
		BGE_SET_TRACE;

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);

		BGE_REMOVE_TRACE;

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseBtnPressedImpl(MouseCodes button)
	{
		BGE_SET_TRACE;

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);

		BGE_REMOVE_TRACE;

		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseBtnReleasedImpl(MouseCodes button)
	{

		BGE_SET_TRACE;

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, (int)button);

		BGE_REMOVE_TRACE;

		return state == GLFW_RELEASE;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		BGE_SET_TRACE;

		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		BGE_REMOVE_TRACE;

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		BGE_SET_TRACE;

		auto [xPos, yPos] = GetMousePos();

		BGE_REMOVE_TRACE;

		return xPos;
	}

	float WindowsInput::GetMouseYImpl()
	{
		BGE_SET_TRACE;

		auto [xPos, yPos] = GetMousePos();

		BGE_REMOVE_TRACE;

		return yPos;
	}
}