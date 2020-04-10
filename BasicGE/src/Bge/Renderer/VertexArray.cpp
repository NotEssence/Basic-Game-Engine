#include "bgepch.h"

#include "VertexArray.h"
#include "Bge/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bge::Gfx
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::GL4:
			return new OpenGLVertexArray();
		default:
			BGE_CORE_ASSERT(false);
			return nullptr;
		}
	}
}
