#include "bgepch.h"

#include "Application.h"

#include "Bge/Logger.h"
#include "Bge/KeyCode.h"
#include "Bge/MouseButtonCodes.h"

#include "Bge/Input.h"

#include <glad/glad.h>

namespace Bge
{
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

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		Gfx::VertexBuffer buffer = Gfx::VertexBuffer::Create(sizeof(vertices), vertices);
		buffer.Bind();
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexshader = R"(
			#version 330 core

			layout(location = 0) in vec3 position;
			out vec3 outPosition;

			void main() 
			{
				gl_Position = vec4(position, 1.0f);
				outPosition = position;
			}	
		)";


		std::string pixelShader = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 outPosition;

			void main() 
			{
				color = vec4(outPosition * 0.5f + 0.5f, 1.0f);
			}	
		)";

		m_Shader = std::make_unique<Gfx::Shader>(vertexshader, pixelShader);

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

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
