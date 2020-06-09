#pragma once

#include <vector>
#include <memory>

class Event;

class EventHandler
{
public:
	EventHandler();
	EventHandler(const EventHandler &other);
	~EventHandler();

	void Invoke();
		
	EventHandler &operator+=(const std::shared_ptr<Event> &event);
	EventHandler &operator-=(const std::shared_ptr<Event> &event);

private:
	std::vector<std::shared_ptr<Event>> events;
};