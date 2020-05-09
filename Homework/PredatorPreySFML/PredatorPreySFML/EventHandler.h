#pragma once

#include "Vector.h"

namespace bme
{
	class Event;

	class EventHandler
	{
	public:
		EventHandler();
		EventHandler(const EventHandler &other);
		~EventHandler();

		void Invoke();
		
		EventHandler &operator+=(Event *event);
		EventHandler &operator-=(Event *event);

	private:
		vector<Event *> events;
	};
}