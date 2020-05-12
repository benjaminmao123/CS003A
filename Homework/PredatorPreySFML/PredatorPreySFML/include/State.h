#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <string>

#include "Vector.h"

namespace bme
{
	class StateTransition;

	class DLLEXPORT State
	{
	public:
		State(const std::string &name);
		virtual ~State();

		virtual void OnStateEnter();
		virtual void OnStateUpdate();
		virtual void OnStateExit();

		State *Evaluate();
		void AddTransition(const StateTransition &transition);
		void SetName(const std::string &name);
		const std::string &GetName() const;
		unsigned int GetID() const;

	private:
		std::string name;
		int id;
		static int nextID;
		vector<StateTransition> transitions;
	};
}