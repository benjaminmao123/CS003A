#include "StateMachine.h"
#include "State.h"
#include "StateTransition.h"

void bme::StateMachine::OnStateEnter()
{

}

void bme::StateMachine::OnStateExit()
{

}

void bme::StateMachine::OnStateUpdate()
{

}

void bme::StateMachine::AddState(State *state)
{
	states.insert(std::make_pair(state->GetID(), state));
}

void bme::StateMachine::AddTransition(State *start, State *end)
{
	start->AddTransition(StateTransition(start, end));
}

void bme::StateMachine::GetState(int id)
{

}

void bme::StateMachine::GetState(const std::string &name)
{

}
