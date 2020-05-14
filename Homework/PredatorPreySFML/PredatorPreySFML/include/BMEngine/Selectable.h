#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>

#include "EventHandler.h"

namespace bme
{
	class DLLEXPORT Selectable
	{
	public:
		Selectable();
		virtual ~Selectable();

		void SetNormalColor(const sf::Color &color);
		void SetPressedColor(const sf::Color &color);
		void SetHighlightedColor(const sf::Color &color);
		void SetSelectedColor(const sf::Color &color);
		void SetDisabledColor(const sf::Color &color);
		void SetIsInteractable(bool state);
		const sf::Color &GetNormalColor() const;
		const sf::Color &GetPressedColor() const;
		const sf::Color &GetHighlightedColor() const;
		const sf::Color &GetSelectedColor() const;
		const sf::Color &GetDisabledColor() const;
		bool GetIsInteractable() const;
		bool GetIsSelected() const;
		void AddEvent(Event *event);
		void RemoveEvent(Event *event);

	protected:
		void SetIsSelected(bool state);
		virtual void OnClick();
		EventHandler &GetOnClickEvents();

	private:
		virtual void CheckSelection() = 0;

		sf::Color normalColor;
		sf::Color highlightedColor;
		sf::Color pressedColor;
		sf::Color selectedColor;
		sf::Color disabledColor;
		bool isInteractable;
		bool isSelected;
		EventHandler onClickEvents;
	};
}