#include "bgepch.h"

#include "Bge/Logger.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Bge/Events/ApplicationEvent.h"
#include "Bge/Events/MouseEvent.h"
#include "Bge/Events/KeyEvent.h"

namespace Bge
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WndProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WndProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		BGE_SET_TRACE;

		Shutdown();

		BGE_REMOVE_TRACE;
	}

	void WindowsWindow::Init(const WndProps& props)
	{
		BGE_SET_TRACE;

		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;


#ifndef BGE_DIST
		Logger::GetCoreLogger()->info("Creating Window \"{0}\": {1}, {2}", m_Data.title, m_Data.width, m_Data.height);
#endif // !BGE_DIST
		
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			BGE_ASSERT(success);

			glfwSetErrorCallback([](int errCode, const char* description)
				{
					BGE_CORE_ERROR("GLFW{0}\t{1}", errCode, description);
				});
			BGE_ASSERT(success)
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		
		m_Context = new Gfx::OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW Event Callbacks

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallbackFunction(event);
			});
		
		BGE_CORE_INFO("Successfully Set Window Size Callbacks");

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallbackFunction(event);

				BGE_CORE_INFO("Window Closed");
			});

		BGE_CORE_INFO("Successfully Set Window Close Callbacks");

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scan, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyPressedEvent keyPressedEvent((KeyCode)key, 0);
				KeyReleasedEvent keyReleasedEvent((KeyCode)key);
				KeyPressedEvent keyRepeatEvent((KeyCode)key, 1);

				switch (action)
				{
				case GLFW_PRESS:
					data.eventCallbackFunction(keyPressedEvent);
					break;
				case GLFW_RELEASE:
					data.eventCallbackFunction(keyReleasedEvent);
					break;
				case GLFW_REPEAT:
					data.eventCallbackFunction(keyRepeatEvent);
					break;
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent keyTypedEvent((KeyCode)character);
				data.eventCallbackFunction(keyTypedEvent);
			});

		BGE_CORE_INFO("Successfully Set Key Callbacks");

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseButtonPressedEvent mouseButtonPressedEvent((MouseCodes)button);
				MouseButtonReleasedEvent mouseButtonReleasedEvent((MouseCodes)button);

				switch (action)
				{
				case GLFW_PRESS:
					data.eventCallbackFunction(mouseButtonPressedEvent);
					break;
				case GLFW_RELEASE:
					data.eventCallbackFunction(mouseButtonReleasedEvent);
					break;
				}
			});

		BGE_CORE_INFO("Successfully Set Mouse Button Callbacks");

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent mouseScrolledEvent((float)xOffset, (float)yOffset);
				data.eventCallbackFunction(mouseScrolledEvent);
			});

		BGE_CORE_INFO("Successfully Set Mouse Scroll Callbacks");

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent mouseMovedEvent((float)xPos, (float)yPos);
				data.eventCallbackFunction(mouseMovedEvent);
			});

		BGE_CORE_INFO("Successfully Set Mouse Move Callbacks");

		BGE_CORE_INFO("Successfully Created Window: \"{0}\"", props.title);

		BGE_REMOVE_TRACE;
	}

	void WindowsWindow::Shutdown()
	{
		BGE_SET_TRACE;

		glfwDestroyWindow(m_Window);

		BGE_CORE_INFO("Successfully Destroyed Window: \"{0}\"", m_Data.title);

		BGE_REMOVE_TRACE;
	}

	void WindowsWindow::Update()
	{
		BGE_SET_TRACE;

		glfwPollEvents();

		m_Context->SwapBuffers();

		BGE_REMOVE_TRACE;
	}

	void WindowsWindow::SetVSync(bool isEnabled)
	{
		BGE_SET_TRACE;

		if (isEnabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.vsync = true;

		BGE_CORE_INFO("Enabled VSync for \"{0}\"", m_Data.title);

		BGE_REMOVE_TRACE;
	}

	bool WindowsWindow::IsVSync() const
	{
		BGE_SET_TRACE;

		return m_Data.vsync;

		BGE_REMOVE_TRACE;
	}
}