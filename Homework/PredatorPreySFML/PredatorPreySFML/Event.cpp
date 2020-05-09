#include "Event.h"

int bme::Event::nextID = 0;

bme::Event::Event()
	:	id(nextID++)
{

}

bme::Event::~Event()
{

}

bool bme::Event::operator==(const Event &rhs) const
{
	return id == rhs.id;
}

bool bme::Event::operator!=(const Event &rhs) const
{
	return id != rhs.id;
}
