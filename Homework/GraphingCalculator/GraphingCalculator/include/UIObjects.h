#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

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
	bool GetIsHighlighted() const;
	void AddEvent(const std::shared_ptr<Event>& event);
	void RemoveEvent(const std::shared_ptr<Event>& event);
	virtual void OnClick();

protected:
	void SetIsSelected(bool state);
	void SetIsHighlighted(bool state);
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
	bool isHighlighted;
};

class Text
{
public:
	Text();

	void Update();
	void Render(sf::RenderWindow& window);

	void Load(const std::string &path);
	void Load(const sf::Font &font);

	void SetFillColor(const sf::Color& color);
	void SetOutlineColor(const sf::Color& color);

	void SetOutlineThickness(float thickness);
	float GetOutlineThickness() const;

	void SetPosition(float x, float y);
	void SetPosition(const sf::Vector2f &pos);
	sf::Vector2f GetPosition() const;

	void SetSize(float width, float height);
	void SetSize(const sf::Vector2f &dims);
	sf::Vector2f GetSize() const;

	void SetCharacterSize(unsigned int size);
	unsigned int GetCharacterSize() const;

	void SetStyle(sf::Text::Style style);

	void SetString(const std::string &str);
	std::string GetString() const;

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
	void Render(sf::RenderWindow& window);

	void Load(const std::string &texturePath, const std::string &fontPath);
	void Load(sf::Texture *texture, const sf::Font &font);

	void SetOutlineColor(const sf::Color& color);
	void SetTextFillColor(const sf::Color& color);
	void SetTextOutlineColor(const sf::Color& color);

	void SetOutlineThickness(float thickness);
	float GetOutlineThickness() const;

	void SetTextOutlineThickness(float thickness);
	float GetTextOutlineThickness() const;

	void SetSize(const sf::Vector2f& dims);
	void SetSize(float x, float y);
	const sf::Vector2f& GetSize() const;

	void SetPosition(const sf::Vector2f& pos);
	void SetPosition(float x, float y);
	const sf::Vector2f& GetPosition() const;

	void SetTextCharacterSize(unsigned int size);
	unsigned int GetTextCharacterSize() const;

	void SetTextStyle(sf::Text::Style style);

	void SetText(const std::string& string);
	std::string GetText() const;

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

	void SetFillColor(const sf::Color& color);
	void SetOutlineColor(const sf::Color &color);
	void SetTextFillColor(const sf::Color& color);
	void SetTextOutlineColor(const sf::Color& color);

	void SetOutlineThickness(float value);
	float GetOutlineThickness() const;

	void SetTextOutlineThickness(float value);
	float GetTextOutlineThickness() const;

	void SetSize(const sf::Vector2f& size);
	void SetSize(float width, float height);
	const sf::Vector2f &GetSize() const;

	void SetPosition(const sf::Vector2f& pos);
	void SetPosition(float x, float y);
	const sf::Vector2f &GetPosition() const;

	void SetTextCharacterSize(unsigned int value);
	unsigned int GetTextCharacterSize() const;

	void SetTextStyle(sf::Text::Style style);

	void SetCurrentString(const std::string &string);
	std::string GetCurrentString() const;

	void GetInput(sf::Uint32 unicode);
	void Clear();

	void AddOnSelectEvent(const std::shared_ptr<Event>& event);
	void AddDeselectEvent(const std::shared_ptr<Event>& event);
	void AddOnValueChangedEvent(const std::shared_ptr<Event>& event);
	void AddOnEndEditEvent(const std::shared_ptr<Event>& event);

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