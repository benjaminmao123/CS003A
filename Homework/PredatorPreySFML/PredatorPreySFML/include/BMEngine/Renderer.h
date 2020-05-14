#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include "Component.h"

namespace bme
{
	class DLLEXPORT Renderer : public Component
	{
	public:
		Renderer(bme::GameObject *owner, bme::Context &context);

		virtual void OnRender();

	protected:
		virtual void Render() = 0;
	};
}