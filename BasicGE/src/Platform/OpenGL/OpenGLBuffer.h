#pragma once

#include "Bge/Renderer/Buffer.h"

namespace Bge::Gfx
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	private:
		BGuint m_RendererID;
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		BGuint m_RendererID;
		BGuint m_Count;
	public:
		OpenGLIndexBuffer(BGuint* indices, size_t size);
		virtual ~OpenGLIndexBuffer();

		virtual BGuint GetCount() const override { return m_Count; };

		virtual void Bind() const override;
		virtual void UnBind() const override;
	};
}
