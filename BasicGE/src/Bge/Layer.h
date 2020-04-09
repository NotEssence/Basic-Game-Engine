#pragma once

#include "bgepch.h"

#include "Bge/Core.h"
#include "Bge/Events/Event.h"

namespace Bge
{
	class BGE_API Layer
	{
	protected:
		std::string m_DebugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }
		
		virtual void OnImGuiRender() { };

		inline const std::string& GetName() const { return m_DebugName; }
	};
}