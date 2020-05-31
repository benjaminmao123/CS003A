#pragma once

#include <vector>

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
	std::vector<Event *> events;
};