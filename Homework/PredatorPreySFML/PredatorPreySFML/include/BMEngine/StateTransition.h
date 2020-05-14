#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <vector>

namespace bme
{
	class State;
	class StateCondition;

	class DLLEXPORT StateTransition
	{
	public:
		StateTransition(State *start, State *dest);

		State *Evaluate();
		void AddCondition(StateCondition *condition);

	private:
		std::vector<StateCondition *> conditions;
		State *start;
		State *dest;
	};
}