#include "bgepch.h"

#include "Bge/Renderer/Buffer.h"

#include "Bge/Renderer/Renderer.h"
#include "Bge/Logger.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bge::Gfx
{
	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::GL4:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			BGE_CORE_ASSERT(false);
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(BGuint* indices, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::GL4:
			return new OpenGLIndexBuffer(indices, size);
		default:
			BGE_CORE_ASSERT(true);
			return nullptr;
		}
	}
}