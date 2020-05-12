#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include "Vector.h"

namespace bme
{
	class Event;

	class DLLEXPORT EventHandler
	{
	public:
		EventHandler();
		EventHandler(const EventHandler &other);
		~EventHandler();

		void Invoke();
		
		EventHandler &operator+=(Event *event);
		EventHandler &operator-=(Event *event);

	private:
		vector<Event *> events;
	};
}