#include "bgepch.h"

#include "OpenGLVertexArray.h"

#include "Bge/Renderer/Buffer.h"

#include <glad/glad.h>

namespace Bge::Gfx
{
	static GLenum ShaderDataType2GLType(Gfx::ShaderDataType type)
	{
		switch (type)
		{
		case Bge::Gfx::ShaderDataType::Int: return GL_INT;
		case Bge::Gfx::ShaderDataType::Int2: return GL_INT;
		case Bge::Gfx::ShaderDataType::Int3: return GL_INT;
		case Bge::Gfx::ShaderDataType::Int4: return GL_INT;
		case Bge::Gfx::ShaderDataType::Float: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Float2: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Float3: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Float4: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Float3x3: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Float4x4: return GL_FLOAT;
		case Bge::Gfx::ShaderDataType::Bool: return GL_BOOL;
		}

		BGE_CORE_ERROR("Unknown Type");
		BGE_CORE_ASSERT(false);

		BGE_REMOVE_TRACE;
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{ 
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{ 
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{ 
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		BGE_CORE_ERROR("Vertex Buffer Has No Layout");
		BGE_CORE_ASSERT(vertexBuffer->GetLayout().GetBufferElems().size());

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		BufferLayout layout = vertexBuffer->GetLayout();
		BGuint index = 0;
		for (auto& elt : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, elt.GetComponentCount(), ShaderDataType2GLType(elt.type), elt.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)elt.offset);

			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);

		BGE_REMOVE_TRACE;
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
