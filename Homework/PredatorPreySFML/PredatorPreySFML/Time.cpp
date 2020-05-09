#include "Time.h"

bme::Time::Time()
	:	deltaTime(0)
{

}

void bme::Time::Update()
{
	deltaTime = clock.restart().asSeconds();
}

float bme::Time::GetDeltaTime() const
{
	return deltaTime;
}
