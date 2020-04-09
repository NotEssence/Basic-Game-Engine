#pragma once

#include "Bge/Core.h"

#include "Bge/KeyCode.h"
#include "Bge/MouseButtonCodes.h"

namespace Bge
{
	class BGE_API Input
	{
	private:
		static Input* s_Instance;
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) = 0;
		virtual bool IsKeyReleasedImpl(KeyCode keycode) = 0;

		virtual bool IsMouseBtnPressedImpl(MouseCodes button) = 0;
		virtual bool IsMouseBtnReleasedImpl(MouseCodes button) = 0;

		virtual std::pair<float, float> GetMousePosImpl() = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	public:
		inline static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); };
		inline static bool IsKeyReleased(KeyCode keycode) { return s_Instance->IsKeyReleasedImpl(keycode); };

		inline static bool IsMouseBtnPressed(MouseCodes button) { return s_Instance->IsMouseBtnPressedImpl(button); };
		inline static bool IsMouseBtnReleased(MouseCodes button) { return s_Instance->IsMouseBtnReleasedImpl(button); };
		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); };
		
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); };
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); };
	};
}