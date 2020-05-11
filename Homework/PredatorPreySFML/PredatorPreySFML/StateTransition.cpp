#include "StateTransition.h"
#include "State.h"

bme::StateTransition::StateTransition(State *start, State *dest)
	: start(start), dest(dest)
{

}
