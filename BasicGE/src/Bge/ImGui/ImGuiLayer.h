#pragma once

#include "Bge/Core.h"

#include "Bge/Layer.h"

#include "Bge/Events/KeyEvent.h"
#include "Bge/Events/MouseEvent.h"
#include "Bge/Events/ApplicationEvent.h"
#include "Bge/Events/Event.h"

#define BGE_BIND_MEMBER_CBFN(x) std::bind(&x, this, std::placeholders::_1)

namespace Bge
{
	class BGE_API ImGuiLayer : public Layer
	{
	private:
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}
