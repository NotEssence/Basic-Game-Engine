#pragma once

#include "Bge/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Bge::Gfx
{
	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WndHandle;
	public:
		OpenGLContext(GLFWwindow* wndHandle);
		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}