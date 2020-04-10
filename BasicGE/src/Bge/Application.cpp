#include "bgepch.h"

#include "Application.h"

#include "Bge/Logger.h"
#include "Bge/KeyCode.h"
#include "Bge/MouseButtonCodes.h"
#include "Bge/Input.h"

#include "Bge/Renderer/Renderer.h"

#include <glad/glad.h>

namespace Bge
{
	// Temporary -- Remove!
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		BGE_SET_TRACE;

		BGE_CORE_INFO("Initializing Application");

		BGE_CORE_ASSERT(!s_Instance)
		
		s_Instance = this;

		Logger::CreateConsoleLogger("bge-events");
		Logger::GetLogger("bge-events")->set_pattern("%^%D %T [%n] [%l]:    %v%$");

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(Gfx::VertexArray::Create());

		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f, 
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};


		m_SquareVertexArray.reset(Gfx::VertexArray::Create());
		std::shared_ptr<Gfx::VertexBuffer> squareVertBuffer;
		squareVertBuffer.reset(Gfx::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVertBuffer->SetLayout({
			{ Gfx::ShaderDataType::Float3, "position" }
		});
		
		m_SquareVertexArray->AddVertexBuffer(squareVertBuffer);

		BGuint squareIndices[] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Gfx::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Gfx::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(BGuint)));

		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string pinkVertexshader = R"(
			#version 330 core

			layout(location = 0) in vec3 position;

			out vec3 outPosition;

			void main() 
			{
				outPosition = position;
				gl_Position = vec4(position, 1.0f);
			}	
		)";


		std::string pinkPixelShader = R"(
			#version 330 core

			layout(location = 0) out vec4 a_Color;
			in vec3 outPosition;

			void main() 
			{
				a_Color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
			}	
		)";

		m_PinkShader.reset(new Gfx::Shader(pinkVertexshader, pinkPixelShader));

		BGE_REMOVE_TRACE;
	}

	Application::~Application()
	{
		m_Window.release();

		BGE_CORE_INFO("Application Shutting down");
		Logger::GetCoreLogger()->flush();
	}

	void Application::Run()
	{
		BGE_SET_TRACE;

		BGE_CORE_INFO("Entering Game Loop . . .");

		while (m_IsRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			Gfx::RendererCmd::Clear({ 1.0f, 0.0f, 1.0f, 1.0f });

			// -------------- Scene -------------- 
			Gfx::Renderer::BeginScene();

			m_PinkShader->Bind();
			Gfx::Renderer::SubmitMesh(m_SquareVertexArray);
			
			Gfx::Renderer::EndScene();
			// -----------------------------------

			Gfx::Renderer::Flush();

			m_PinkShader->Bind();
			m_SquareVertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			
			for (auto layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			
			m_ImGuiLayer->End();

			m_Window->Update();
		}

		BGE_REMOVE_TRACE;
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispather(event);

		dispather.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.m_Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}
