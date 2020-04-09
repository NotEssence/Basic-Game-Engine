#pragma once

namespace Bge::Gfx
{
	enum class RendererAPI
	{
		None = 0,
		GL4
		// In The Future
		// DX11,
		// VULKAN
	};

	class Renderer
	{
	private:
		static RendererAPI s_RendererApi;
	public:
		__forceinline static RendererAPI GetAPI() { return s_RendererApi; }
	};
}
