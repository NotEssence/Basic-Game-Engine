#pragma once

#include "Event.h"

#include "Bge/Core.h"

#include "Bge/KeyCode.h"

namespace Bge
{
	class BGE_API KeyEvent : public Event
	{
	protected:
		KeyCode m_KeyCode;

		KeyEvent(KeyCode keyCode)
			: m_KeyCode(keyCode) { }
	public:
		inline KeyCode GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class BGE_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
	public:
		KeyPressedEvent(KeyCode keyCode, int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstream;
			sstream << "KeyPressedEvent: "<< (int)m_KeyCode << "(" << m_RepeatCount << ")";
			return sstream.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class BGE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode)
		{ }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstream;
			sstream << "KeyPressedEvent: " << (int)m_KeyCode;
			return sstream.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class BGE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keyCode)
			: KeyEvent(keyCode)
		{ }

		std::string ToString() const override
		{
			BGE_SET_TRACE;

			std::stringstream sstream;
			sstream << "KeyTypedEvent: " << (int)m_KeyCode;
			return sstream.str();

			BGE_REMOVE_TRACE;
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}