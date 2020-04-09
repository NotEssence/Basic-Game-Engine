#include "bgepch.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Bge/Core.h"
#include "Bge/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bge::Gfx
{
	OpenGLContext::OpenGLContext(GLFWwindow* wndHandle)
		: m_WndHandle(wndHandle)
	{ 
		BGE_CORE_ASSERT(wndHandle)
	}

	OpenGLContext::~OpenGLContext()
	{ }

	void OpenGLContext::Init()
	{ 
		BGE_SET_TRACE;

		glfwMakeContextCurrent(m_WndHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BGE_CORE_ASSERT(status);

		BGE_REMOVE_TRACE;
	}

	void OpenGLContext::SwapBuffers()
	{
		BGE_SET_TRACE;

		glfwSwapBuffers(m_WndHandle);

		BGE_REMOVE_TRACE;
	}
}