#pragma once

#include <Bge/Bge.h>

class ExampleLayer : public Bge::Layer
{
public:
	ExampleLayer();
	~ExampleLayer();

	void OnUpdate() override;

	void OnEvent(Bge::Event& event) override;
	void OnImGuiRender() override;
};
