#include "EventHandler.h"
#include "Event.h"

EventHandler::EventHandler()
{

}

EventHandler::EventHandler(const EventHandler& other)
{
	for (auto& e : events)
		operator+=(e);
}

EventHandler::~EventHandler()
{

}

void EventHandler::Invoke()
{
	for (auto& e : events)
		e->Invoke();
}

EventHandler& EventHandler::operator+=(const std::shared_ptr<Event>& event)
{
	for (const auto& e : events)
	{
		if (e == event)
			return *this;
	}

	events.push_back(event);

	return *this;
}

EventHandler& EventHandler::operator-=(const std::shared_ptr<Event>& event)
{
	int index = 0;

	for (auto& e : events)
	{
		if (e == event)
		{
			events.erase(events.begin() + index);
			break;
		}

		++index;
	}

	return *this;
}
