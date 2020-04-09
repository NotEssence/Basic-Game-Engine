#pragma once

#include "Bge/Window.h"
#include <Bge/Renderer/GraphicsContext.h>

#include <GLFW/glfw3.h>

namespace Bge
{
	class WindowsWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vsync;

			EventCallbackFunc eventCallbackFunction;
		};

		WindowData m_Data;

		GLFWwindow* m_Window;
		Gfx::GraphicsContext* m_Context;

		void Init(const WndProps& props);
		void Shutdown();

	public:
		WindowsWindow(const WndProps& props);
		virtual ~WindowsWindow();

		void Update() override;

		__forceinline unsigned int GetWidth() const override { return m_Data.width; }
		__forceinline unsigned int GetHeight() const override { return m_Data.height; }

		__forceinline virtual void* GetNativeWindow() const override { return m_Window; };

		__forceinline void SetEventCallback(const EventCallbackFunc& e) override 
		{
			m_Data.eventCallbackFunction = e;
		}

		void SetVSync(bool isEnabled) override;
		bool IsVSync() const override;
	};
}
