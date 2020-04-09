#include <string>
#include <iostream>

#include <Bge/Bge.h>

#include <imgui/imgui.h>

class ExampleLayer : public Bge::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{
		Bge::Logger::CreateConsoleLogger("app-events");
		Bge::Logger::GetLogger("app-events")->set_pattern("%^%D %T [%n] [%l]: %v %$");
	}

	void OnUpdate() override
	{
		BGE_SET_TRACE;
		BGE_REMOVE_TRACE;
	}

	void OnEvent(Bge::Event& event) override
	{
		BGE_SET_TRACE;
		BGE_REMOVE_TRACE;
	}

	void OnImGuiRender() override
	{
		BGE_SET_TRACE;

		// static bool show = true;
		// ImGui::ShowDemoWindow(&show);

		BGE_REMOVE_TRACE;
	}
};

class Application : public Bge::Application
{
public:
	Application()
	{
		BGE_SET_TRACE;

		PushLayer(new ExampleLayer());

		BGE_REMOVE_TRACE;
	}

	~Application()
	{
		BGE_SET_TRACE;
		BGE_REMOVE_TRACE;
	}
};

BGE_IMPLEMENT_APP(Application)
