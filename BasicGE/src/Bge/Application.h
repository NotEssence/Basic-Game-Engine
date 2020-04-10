#pragma once

#include "bgepch.h"

#include "Bge/Window.h"
#include "Bge/LayerStack.h"
#include "Core.h"

#include "Bge/ImGui/ImGuiLayer.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

#include <cstdint>

// --------------- Temporary ---------------
#include "Bge/Renderer/Shader.h"
#include "Bge/Renderer/Buffer.h"
#include "Bge/Renderer/VertexArray.h"
// -----------------------------------------

namespace Bge
{
	class BGE_API Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		bool m_IsRunning = true;

		static Application* s_Instance;

		std::shared_ptr<Gfx::VertexArray> m_VertexArray;
		std::shared_ptr<Gfx::VertexArray> m_SquareVertexArray;
		std::shared_ptr<Gfx::Shader> m_Shader;
		std::shared_ptr<Gfx::Shader> m_PinkShader;
		
		
		bool OnWindowClose(WindowCloseEvent& e);
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	};
}

