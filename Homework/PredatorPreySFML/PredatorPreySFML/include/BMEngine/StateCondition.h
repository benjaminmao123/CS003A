#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

namespace bme
{
	class DLLEXPORT StateCondition
	{
	public:
		virtual ~StateCondition();

		virtual bool Evaluate() const = 0;
	};
}