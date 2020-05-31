#include "Event.h"

int Event::nextID = 0;

Event::Event()
	: id(nextID++)
{

}

Event::~Event()
{

}

bool Event::operator==(const Event &rhs) const
{
	return id == rhs.id;
}

bool Event::operator!=(const Event &rhs) const
{
	return id != rhs.id;
}
