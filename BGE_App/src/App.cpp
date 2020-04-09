#include <Bge/Bge.h>
#include "ExampleLayer.h"

class Application : public Bge::Application
{
public:
	Application()
	{
		PushLayer(new ExampleLayer());
	}

	~Application()
	{
	}
};

BGE_IMPLEMENT_APP(Application)
