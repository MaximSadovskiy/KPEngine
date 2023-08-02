#pragma once
#include <iostream>
struct GLFWwindow;

enum EventType
{
	WindowResizeEvent = 0, WindowCloseEvent,
	MouseMove,
	KeyInput,
};
namespace Kpe {
#define KPE_DEFINE_EVENT_TYPE(type) const char* getTypeName() override { return #type; }\
						  EventType getType() override { return EventType::type; }
	class Event
	{
	public:
		virtual EventType getType();
		virtual const char* getTypeName();
		template <typename Expected, typename E>
		static void Dispatch(Event& event)
		{
			/*if (Expected == E::) std::cout << "popal\n";
			else std::cout << "ne popal\n";*/
		}
	};
}