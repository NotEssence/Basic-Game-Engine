#pragma once

#include "Bge/BgeTypes.h"

#include "Bge/Logger.h"

namespace Bge::Gfx
{
	enum class ShaderDataType
	{
		None = 0,

		Int,
		Int2,
		Int3,
		Int4,

		Float,
		Float2,
		Float3,
		Float4,

		Float3x3,
		Float4x4,

		Bool
	};

	static BGuint ShaderDataTypeSize(ShaderDataType dataType)
	{
		switch (dataType)
		{
		case ShaderDataType::Int: return sizeof(int);
		case ShaderDataType::Int2: return sizeof(int) * 2;
		case ShaderDataType::Int3: return sizeof(int) * 3;
		case ShaderDataType::Int4: return sizeof(int) * 4;
		case ShaderDataType::Float: return sizeof(float);
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::Float3: return	sizeof(float) * 3;
		case ShaderDataType::Float4: return	sizeof(float) * 4;
		case ShaderDataType::Float3x3: return sizeof(float) * 3 * 3;
		case ShaderDataType::Float4x4: return sizeof(float) * 4 * 4;
		case ShaderDataType::Bool: return sizeof(bool);
		}

		BGE_CORE_ERROR("Unknown Shader Data Type")
		BGE_CORE_ASSERT(false);

		BGE_REMOVE_TRACE;
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType type;
		std::string name;

		BGuint offset;
		BGuint size;

		bool normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: type(type), name(name), offset(0), size(ShaderDataTypeSize(type)), normalized(normalized)
		{
			size = ShaderDataTypeSize(type);
		}

		BGuint GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Int2: return 1 * 2;
			case ShaderDataType::Int3: return 1 * 3;
			case ShaderDataType::Int4: return 1 * 4;
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Float2: return 1 * 2;
			case ShaderDataType::Float3: return	1 * 3;
			case ShaderDataType::Float4: return	1 * 4;
			case ShaderDataType::Float3x3: return 1 * 3 * 3;
			case ShaderDataType::Float4x4: return 1 * 4 * 4;
			case ShaderDataType::Bool: return 1;
			}

			BGE_CORE_ERROR("Unknown Shader Data Type")
			BGE_CORE_ASSERT(false);

			return 0;
		}
	};

	class BufferLayout
	{
	private:
		std::vector<BufferElement> m_BufferElems;
		BGuint m_Stride = 0;
		
		void GetBufferElemOffsetNStride()
		{
			BGuint offset = 0;
			m_Stride = 0;

			for (auto& elt : m_BufferElems)
			{
				elt.offset = offset;
				offset += elt.size;
				m_Stride += elt.size;
			}
		}
	public:
		std::vector<BufferElement>::iterator begin() { return m_BufferElems.begin(); }
		std::vector<BufferElement>::iterator end() { return m_BufferElems.end(); }

		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elems)
			: m_BufferElems(elems)
		{
			GetBufferElemOffsetNStride();
		}

		__forceinline const std::vector<BufferElement>& GetBufferElems() const { return m_BufferElems; }
		__forceinline BGuint GetStride() const { return m_Stride; }
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual BGuint GetCount() const = 0;

		static IndexBuffer* Create(BGuint* vertices, size_t count);
	};
}