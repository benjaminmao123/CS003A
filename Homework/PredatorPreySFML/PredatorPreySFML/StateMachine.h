#pragma once

#include <string>

#include "HashMap.h"

namespace bme
{
	class State;

	class StateMachine
	{
	public:
		void OnStateEnter();
		void OnStateExit();
		void OnStateUpdate();

		void AddState(State *state);
		void AddTransition(State *start, State *end);
		void GetState(int id);
		void GetState(const std::string &name);

	private:
		unordered_map<int, State *> states;
		State *activeState;
	};
}