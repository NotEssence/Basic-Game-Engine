#pragma once

#include "bgepch.h"

#include "Application.h"
#include "Logger.h"

#define BGE_IMPLEMENT_APP(bgeApp)										\
int main(int argc, char** argv)											\
{																		\
	Bge::Logger::Init();    								            \
	std::unique_ptr<Bge::Application> application = std::make_unique<bgeApp>();	\
	application->Run();													\
}
