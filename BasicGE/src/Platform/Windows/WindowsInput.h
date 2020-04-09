#pragma once

#include "Bge/Input.h"

namespace Bge
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) override;
		virtual bool IsKeyReleasedImpl(KeyCode keycode) override;

		virtual bool IsMouseBtnPressedImpl(MouseCodes button) override;
		virtual bool IsMouseBtnReleasedImpl(MouseCodes button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}