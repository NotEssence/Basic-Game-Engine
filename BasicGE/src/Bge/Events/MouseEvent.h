#pragma once

#include "Event.h"

#include "Bge/MouseButtonCodes.h"

namespace Bge
{
	class BGE_API MouseMovedEvent : public Event
	{
	private:
		float m_MouseX, m_MouseY;
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstring;
			sstring << "MouseMoved: " << m_MouseX << ", " << m_MouseY;
			return sstring.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class BGE_API MouseScrolledEvent : public Event
	{
	private:
		float m_XOffset, m_YOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) { }

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstring;
			sstring << "MouseScrolled: " << m_XOffset << ", " << m_YOffset;
			return sstring.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class BGE_API MouseButtonEvent : public Event
	{
	protected:
		MouseCodes m_Button;

		MouseButtonEvent(MouseCodes button)
			: m_Button(button) { }
	public:
		inline MouseCodes GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class BGE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCodes button)
			: MouseButtonEvent(button)
		{ }
		
		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstream;
			sstream << "MouseButtonPressedEvent: " << (int)m_Button;
			return sstream.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class BGE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCodes button)
			: MouseButtonEvent(button)
		{ }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstream;
			sstream << "MouseButtonReleasedEvent: " << (int)m_Button;
			return sstream.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}