#include "bgepch.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Bge/Logger.h"

#include <glad/glad.h>

namespace Bge::Gfx
{
	// VertexBuffer
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		BGE_CORE_ASSERT(vertices != nullptr);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{ 
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// IndexBuffer
	OpenGLIndexBuffer::OpenGLIndexBuffer(float* indices, size_t size)
	{ 
		glCreateBuffers(1, &m_RendererID);
		BGE_CORE_ASSERT(indices != nullptr);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{ 
	
	}
	
	void OpenGLIndexBuffer::Bind() const
	{
	
	}
	
	void OpenGLIndexBuffer::UnBind() const
	{
	
	}
}