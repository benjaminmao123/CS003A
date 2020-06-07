#pragma once

#include <SFML\Graphics.hpp>

#include "Event.h"
#include "EventHandler.h"
#include "InputManager.h"

enum class HAlign
{
	Left,
	Center,
	Right
};

enum class VAlign
{
	Top,
	Middle,
	Bottom
};

class Selectable
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
	virtual void OnClick();

protected:
	void SetIsSelected(bool state);
	EventHandler &GetOnClickEvents();
	InputManager input;

private:
	virtual void CheckSelection(sf::RenderWindow &window) = 0;

	sf::Color normalColor;
	sf::Color highlightedColor;
	sf::Color pressedColor;
	sf::Color selectedColor;
	sf::Color disabledColor;
	bool isInteractable;
	bool isSelected;
	EventHandler onClickEvents;
};

class Text
{
public:
	Text();

	void Update();
	void Load(const std::string &path);
	void Load(const sf::Font &font);
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f &pos);
	void SetSize(float width, float height);
	void SetSize(const sf::Vector2f &dims);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	void SetString(const std::string &str);
	void Render(sf::RenderWindow &window);
	std::string GetString() const;
	void SetColor(const sf::Color &color);
	void SetCharacterSize(float size);
	void SetStyle(sf::Text::Style style);

private:
	void AlignText();

	sf::Text text;
	sf::Font font;
	HAlign hAlign;
	VAlign vAlign;
	sf::FloatRect rect;
};

class Button : public Selectable
{
public:
	Button();

	void Update();
	void Load(const std::string &texturePath, const std::string &fontPath);
	void Load(sf::Texture *texture, const sf::Font &font);
	void Render(sf::RenderWindow &window);
	std::string GetLabel() const;
	const sf::Vector2f &GetSize() const;
	const sf::Vector2f &GetPosition() const;
	void SetSize(const sf::Vector2f &dims);
	void SetSize(float x, float y);
	void SetPosition(const sf::Vector2f &pos);
	void SetPosition(float x, float y);
	void SetTextColor(const sf::Color &color);
	void SetLabelFontSize(float size);
	void SetLabel(const std::string &string);

private:
	void ComputeBounds();
	virtual void CheckSelection(sf::RenderWindow &window) override;

	sf::RectangleShape frame;
	sf::FloatRect bounds;
	Text text;
	sf::Texture texture;
};

class InputField : public Selectable
{
public:
	InputField();

	void Update();
	void Render(sf::RenderWindow &window);

	void Load(const std::string &texturePath, const std::string &fontPath);
	void Load(sf::Texture *texture, const sf::Font &font);
	void SetOutlineColor(const sf::Color &color);
	void SetOutlineThickness(const float value);
	void SetSize(const sf::Vector2f &size);
	void SetSize(const float width, const float height);
	void SetPosition(const sf::Vector2f &pos);
	void SetPosition(float x, float y);
	const sf::Vector2f &GetSize() const;
	const sf::Vector2f &GetPosition() const;
	void SetCurrentString(const std::string &string);
	std::string GetCurrentString() const;
	void GetInput(sf::Uint32 unicode);
	void Clear();
	void SetTextColor(const sf::Color &color);

	void AddOnSelectEvent(Event *event);
	void AddDeselectEvent(Event *event);
	void AddOnValueChangedEvent(Event *event);
	void AddOnEndEditEvent(Event *event);

	void OnSelect();
	void OnDeselect();
	void OnValueChanged();
	void OnEndEdit();

private:
	void ComputeBounds();
	virtual void CheckSelection(sf::RenderWindow &window) override;

	sf::RectangleShape field;
	Text text;
	EventHandler onSelectEvents;
	EventHandler onDeselectEvents;
	EventHandler onValueChangedEvents;
	EventHandler onEndEditEvents;
	sf::FloatRect bounds;
	bool isSelected;
	std::string currentString;
	sf::Texture texture;
};