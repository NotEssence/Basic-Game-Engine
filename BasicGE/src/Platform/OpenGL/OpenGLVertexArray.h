#pragma once

#include "Bge/Renderer/VertexArray.h"

namespace Bge::Gfx
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		BGuint m_RendererID;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const 
			override { return m_IndexBuffer; };
	};
}
