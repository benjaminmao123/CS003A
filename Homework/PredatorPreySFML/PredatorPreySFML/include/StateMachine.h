#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <string>
#include <unordered_map>

#include "Component.h"

namespace bme
{
	class State;

	class DLLEXPORT StateMachine : public Component
	{
	public:
		StateMachine(GameObject *owner, Context &context);

		virtual void Start() override;
		virtual void Update() override;

		void AddState(State *state);
		void AddTransition(State *start, State *end);
		State *GetState(int id);

	private:
		void Evaluate();

		std::unordered_map<int, State *> states;
		State *activeState;
	};
}