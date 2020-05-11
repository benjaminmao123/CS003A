#include "State.h"
#include "StateTransition.h"

int bme::State::nextID = 0;

bme::State::State(const std::string &name)
	: name(name), id(nextID++)
{

}

bme::State::~State()
{

}

void bme::State::OnStateEnter()
{

}

void bme::State::OnStateUpdate()
{

}

void bme::State::OnStateExit()
{

}

void bme::State::AddTransition(const StateTransition &transition)
{
	transitions.push_back(transition);
}

void bme::State::SetName(const std::string &name)
{
	this->name = name;
}

const std::string &bme::State::GetName() const
{
	return name;
}

int bme::State::GetID() const
{
	return id;
}
