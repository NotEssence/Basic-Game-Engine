#pragma once

#include <string>
#include "Bge/BgeTypes.h"

namespace Bge::Gfx
{
	enum class ShaderType
	{
		Vertex,
		Pixel
	};

	class Shader
	{
	private:
		BGuint m_RendererID;
	public:
		Shader(const std::string& vertexSrc, const std::string& pixelSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;
	};
}
