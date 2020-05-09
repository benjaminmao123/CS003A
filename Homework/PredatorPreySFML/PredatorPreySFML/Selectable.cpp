#include "Selectable.h"

bme::Selectable::Selectable()
	:	normalColor(sf::Color::White), highlightedColor(sf::Color::White),
		pressedColor(sf::Color::White), selectedColor(sf::Color::White), 
		disabledColor(sf::Color::White), isInteractable(true),
		isSelected(false)
{

}

void bme::Selectable::SetNormalColor(const sf::Color &color)
{
	normalColor = color;
}

void bme::Selectable::SetPressedColor(const sf::Color &color)
{
	pressedColor = color;
}

void bme::Selectable::SetHighlightedColor(const sf::Color &color)
{
	highlightedColor = color;
}

void bme::Selectable::SetSelectedColor(const sf::Color &color)
{
	selectedColor = color;
}

void bme::Selectable::SetDisabledColor(const sf::Color &color)
{
	disabledColor = color;
}

void bme::Selectable::SetIsInteractable(bool state)
{
	isInteractable = state;
}

const sf::Color &bme::Selectable::GetNormalColor() const
{
	return normalColor;
}

const sf::Color &bme::Selectable::GetPressedColor() const
{
	return pressedColor;
}

const sf::Color &bme::Selectable::GetHighlightedColor() const
{
	return highlightedColor;
}

const sf::Color &bme::Selectable::GetSelectedColor() const
{
	return selectedColor;
}

const sf::Color &bme::Selectable::GetDisabledColor() const
{
	return disabledColor;
}

bool bme::Selectable::GetIsInteractable() const
{
	return isInteractable;
}

bool bme::Selectable::GetIsSelected() const
{
	return isSelected;
}

void bme::Selectable::AddEvent(Event *event)
{
	onClickEvents += event;
}

void bme::Selectable::RemoveEvent(Event *event)
{
	onClickEvents -= event;
}

void bme::Selectable::OnClick()
{
	onClickEvents.Invoke();
}

bme::EventHandler &bme::Selectable::GetOnClickEvents()
{
	return onClickEvents;
}

void bme::Selectable::SetIsSelected(bool state)
{
	isSelected = true;
}

