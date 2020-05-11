#pragma once

namespace bme
{
	class State;

	class StateTransition
	{
	public:
		StateTransition(State *start, State *dest);

	private:
		State *start;
		State *dest;
	};
}