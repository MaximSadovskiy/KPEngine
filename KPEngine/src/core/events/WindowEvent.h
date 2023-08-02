#pragma once
#include "Event.h"

namespace Kpe {
	class WindowResizeEvent : public Event {
	public:
		KPE_DEFINE_EVENT_TYPE(WindowResizeEvent);
		WindowResizeEvent() = default;
	};
	class WindowCloseEvent : public Event {
	public:
		KPE_DEFINE_EVENT_TYPE(WindowCloseEvent);
		WindowCloseEvent() = default;
	};
}

