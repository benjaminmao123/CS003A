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

protected:
	void SetIsSelected(bool state);
	virtual void OnClick();
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
	sf::Text &GetText();
	sf::FloatRect &GetRect();
	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f &pos);
	void SetSize(float width, float height);
	void SetSize(const sf::Vector2f &dims);
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	void SetText(const std::string &str);
	void Render(sf::RenderWindow &window);
	const std::string &GetString() const;

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
	sf::RectangleShape &GetFrame();
	void Render(sf::RenderWindow &window);
	Text &GetLabel();
	sf::Vector2f GetSize() const;
	void SetSize(const sf::Vector2f &dims);
	void SetSize(float x, float y);
	void SetPosition(const sf::Vector2f &pos);
	void SetPosition(float x, float y);

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
	const sf::Vector2f &GetSize() const;
	void SetCurrentString(const sf::String &string);
	const std::string &GetCurrentString() const;
	sf::RectangleShape &GetField();
	void GetInput(sf::Uint32 unicode);
	Text &GetText();
	void Clear();
	void SetText(const std::string &str);

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