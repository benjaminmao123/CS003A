#include "EventHandler.h"
#include "Event.h"

bme::EventHandler::EventHandler()
{

}

bme::EventHandler::EventHandler(const EventHandler &other)
{
	for (auto &event : events)
		operator+=(event);
}

bme::EventHandler::~EventHandler()
{
	for (auto &event : events)
		delete event;

	events.clear();
}

void bme::EventHandler::Invoke()
{
	for (auto &i : events)
		i->Invoke();
}

bme::EventHandler &bme::EventHandler::operator+=(Event *event)
{
	for (const auto &i : events)
	{
		if (i == event)
			return *this;
	}

	events.push_back(event);

	return *this;
}

bme::EventHandler &bme::EventHandler::operator-=(Event *event)
{
	int index = 0;

	for (auto &i : events)
	{
		if (i == event)
		{
			events.erase(index);
			break;
		}

		++index;
	}

	return *this;
}
