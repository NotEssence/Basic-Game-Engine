#pragma once

#include "bgepch.h"

#include "Bge/Core.h"
#include "Bge/Events/Event.h"

namespace Bge
{

	struct WndProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WndProps(const std::string& title = "Basic Game Engine", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height) {  }
	};

	class BGE_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool isEnabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WndProps& props = WndProps());
	};
}