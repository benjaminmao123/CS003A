#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>

namespace bme
{
	class GameObject;
	class Context;

	class DLLEXPORT Component
	{
	public:
		Component(GameObject *owner, Context &context);
		virtual ~Component();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual Component *Clone(GameObject *owner) = 0;

		bool GetIsEnabled() const;
		void SetIsEnabled(bool state);
		bool IsAwakeCalled() const;
		bool IsStartCalled() const;
		int GetExecutionOrder() const;

	protected:
		void SetExecutionOrder(int value);
		GameObject *GetOwner();
		sf::Transformable &GetTransformable();
		const sf::Transform &GetWorldTransform() const;
		Context &GetContext();

	private:
		GameObject *owner;
		Context &context;
		bool isEnabled;
		bool isAwakeCalled;
		bool isStartCalled;
		int executionOrder;
	};
}