#pragma once

#include "Legio/LGCore.h"

#include <string.h>
#include <functional>

namespace Legio {


	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication	BIT(0),
		EventCategoryInput			BIT(1),
		EventCategoryKeyboard		BIT(2),
		EventCategoryMouse			BIT(3),
		EventCategoryMouseButton	BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() { return GetStaticType(); }\
							   virtual const char* GetName() { return ##type; }
}
