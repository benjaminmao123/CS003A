#include "Resource.h"

int bme::Resource::nextID = 0;

bme::Resource::Resource()
	:	id(nextID++)
{

}

bme::Resource::~Resource()
{

}

const std::string &bme::Resource::Path() const
{
	return path;
}

int bme::Resource::ID() const
{
	return id;
}
