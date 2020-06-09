#include "UIObjects.h"

Selectable::Selectable()
	: normalColor(sf::Color::White), highlightedColor(sf::Color::White),
	pressedColor(sf::Color::White), selectedColor(sf::Color::White),
	disabledColor(sf::Color::White), isInteractable(true),
	isSelected(false), isHighlighted(false)
{

}

Selectable::~Selectable()
{

}

void Selectable::SetNormalColor(const sf::Color& color)
{
	normalColor = color;
}

void Selectable::SetPressedColor(const sf::Color& color)
{
	pressedColor = color;
}

void Selectable::SetHighlightedColor(const sf::Color& color)
{
	highlightedColor = color;
}

void Selectable::SetSelectedColor(const sf::Color& color)
{
	selectedColor = color;
}

void Selectable::SetDisabledColor(const sf::Color& color)
{
	disabledColor = color;
}

void Selectable::SetIsInteractable(bool state)
{
	isInteractable = state;
}

const sf::Color& Selectable::GetNormalColor() const
{
	return normalColor;
}

const sf::Color& Selectable::GetPressedColor() const
{
	return pressedColor;
}

const sf::Color& Selectable::GetHighlightedColor() const
{
	return highlightedColor;
}

const sf::Color& Selectable::GetSelectedColor() const
{
	return selectedColor;
}

const sf::Color& Selectable::GetDisabledColor() const
{
	return disabledColor;
}

bool Selectable::GetIsInteractable() const
{
	return isInteractable;
}

bool Selectable::GetIsSelected() const
{
	return isSelected;
}

bool Selectable::GetIsHighlighted() const
{
	return isHighlighted;
}

void Selectable::AddEvent(const std::shared_ptr<Event>& event)
{
	onClickEvents += event;
}

void Selectable::RemoveEvent(const std::shared_ptr<Event>& event)
{
	onClickEvents -= event;
}

void Selectable::OnClick()
{
	SetIsHighlighted(false);
	onClickEvents.Invoke();
}

EventHandler& Selectable::GetOnClickEvents()
{
	return onClickEvents;
}

void Selectable::SetIsSelected(bool state)
{
	isSelected = true;
}

void Selectable::SetIsHighlighted(bool state)
{
	isHighlighted = state;
}

Text::Text()
	: hAlign(HAlign::Center),
	vAlign(VAlign::Middle), rect(0, 0, 100, 100)
{

}

void Text::Update()
{
	AlignText();
}

void Text::Render(sf::RenderWindow &window)
{
	window.draw(text);
}

void Text::Load(const std::string& path)
{
	if (font.loadFromFile(path))
		text.setFont(font);
}

void Text::Load(const sf::Font& font)
{
	text.setFont(font);
}

void Text::SetFillColor(const sf::Color &color)
{
	text.setFillColor(color);
}

void Text::SetOutlineColor(const sf::Color& color)
{
	text.setOutlineColor(color);
}

void Text::SetOutlineThickness(float thickness)
{
	text.setOutlineThickness(thickness);
}

float Text::GetOutlineThickness() const
{
	return text.getOutlineThickness();
}

void Text::SetPosition(float x, float y)
{
	text.setPosition(x, y);
	rect.left = x;
	rect.top = y;
}

void Text::SetPosition(const sf::Vector2f &pos)
{
	text.setPosition(pos);
	rect.left = pos.x;
	rect.top = pos.y;
}

sf::Vector2f Text::GetPosition() const
{
	return sf::Vector2f(rect.left, rect.top);
}

void Text::SetSize(float width, float height)
{
	rect.width = width;
	rect.height = height;
}

void Text::SetSize(const sf::Vector2f &dims)
{
	rect.height = dims.x;
	rect.width = dims.y;
}

sf::Vector2f Text::GetSize() const
{
	return sf::Vector2f(rect.width, rect.height);
}

void Text::SetCharacterSize(unsigned int size)
{
	text.setCharacterSize(size);
}

unsigned int Text::GetCharacterSize() const
{
	return text.getCharacterSize();
}

void Text::SetStyle(sf::Text::Style style)
{
	text.setStyle(style);
}

void Text::SetString(const std::string &str)
{
	text.setString(str);
}

std::string Text::GetString() const
{
	return text.getString().toAnsiString();
}

void Text::AlignText()
{
	float x, y;
	text.setPosition(rect.left, rect.top);

	switch (hAlign)
	{
	case HAlign::Left:
		text.setPosition(text.getPosition());
		break;
	case HAlign::Center:
		x = (text.getPosition().x + ((rect.width / 2)) - (text.getLocalBounds().width / 2));
		text.setPosition(x, text.getPosition().y);
		break;
	case HAlign::Right:
		x = (text.getPosition().x + rect.width) - text.getLocalBounds().width;
		text.setPosition(x, text.getPosition().y);
		break;
	default:
		break;
	}

	switch (vAlign)
	{
	case VAlign::Top:
		text.setPosition(text.getPosition());
		break;
	case VAlign::Middle:
		y = (text.getPosition().y + (rect.height / 2)) - (text.getCharacterSize() / 1.5f);
		text.setPosition(text.getPosition().x, y);
		break;
	case VAlign::Bottom:
		y = (text.getPosition().y + rect.height - 4) - text.getLocalBounds().height;
		text.setPosition(text.getPosition().x, y);
		break;
	default:
		break;
	}
}

Button::Button()
	: frame(sf::Vector2f(100, 100))
{
	frame.setFillColor(GetNormalColor());
}

void Button::Update()
{
	ComputeBounds();
	text.SetSize(bounds.width, bounds.height);
	text.SetPosition(frame.getPosition());
	text.Update();
}

void Button::Render(sf::RenderWindow &window)
{
	if (GetIsInteractable())
	{
		frame.setFillColor(GetNormalColor());
		CheckSelection(window);
	}
	else
		frame.setFillColor(GetDisabledColor());

	window.draw(frame);
	text.Render(window);
}

void Button::SetOutlineColor(const sf::Color& color)
{
	frame.setOutlineColor(color);
}

void Button::SetTextFillColor(const sf::Color& color)
{
	text.SetFillColor(color);
}

void Button::SetTextOutlineColor(const sf::Color& color)
{
	text.SetFillColor(color);
}

void Button::SetOutlineThickness(float thickness)
{
	frame.setOutlineThickness(thickness);
}

float Button::GetOutlineThickness() const
{
	return frame.getOutlineThickness();
}

void Button::SetTextOutlineThickness(float thickness)
{
	text.SetOutlineThickness(thickness);
}

float Button::GetTextOutlineThickness() const
{
	return text.GetOutlineThickness();
}

void Button::SetSize(const sf::Vector2f &dims)
{
	frame.setSize(dims);
	bounds.width = dims.x;
	bounds.height = dims.y;
}

void Button::SetSize(float x, float y)
{
	frame.setSize(sf::Vector2f(x, y));
	bounds.width = x;
	bounds.height = y;
}

const sf::Vector2f& Button::GetSize() const
{
	return frame.getSize();
}

void Button::SetPosition(const sf::Vector2f &pos)
{
	frame.setPosition(pos);
	bounds.left = pos.x;
	bounds.top = pos.y;
}

void Button::SetPosition(float x, float y)
{
	frame.setPosition(x, y);
	bounds.left = x;
	bounds.top = y;
}

const sf::Vector2f& Button::GetPosition() const
{
	return frame.getPosition();
}

void Button::SetTextCharacterSize(unsigned int size)
{
	text.SetCharacterSize(size);
}

unsigned int Button::GetTextCharacterSize() const
{
	return text.GetCharacterSize();
}

void Button::SetTextStyle(sf::Text::Style style)
{
	text.SetStyle(style);
}

void Button::SetText(const std::string &string)
{
	text.SetString(string);
}

std::string Button::GetText() const
{
	return text.GetString();
}

void Button::CheckSelection(sf::RenderWindow &window)
{
	ComputeBounds();

	sf::Vector2f mousePosition = sf::Vector2f(
		float(input.GetMousePosition(window).x),
		float(input.GetMousePosition(window).y));

	SetIsHighlighted(false);

	if (bounds.contains(mousePosition))
	{
		frame.setFillColor(GetHighlightedColor());
		SetIsHighlighted(true);

		if (input.GetMouseButton(sf::Mouse::Left))
			frame.setFillColor(GetPressedColor());

		if (input.GetMouseButton(sf::Mouse::Left))
			OnClick();
	}
}

void Button::Load(const std::string &texturePath, const std::string &fontPath)
{
	if (texturePath != "")
		if (texture.loadFromFile(texturePath))
			frame.setTexture(&texture);

	if (fontPath != "")
		text.Load(fontPath);
}

void Button::Load(sf::Texture *texture, const sf::Font &font)
{
	if (texture)
		frame.setTexture(texture);
	text.Load(font);
}

void Button::ComputeBounds()
{
	bounds.left = frame.getPosition().x;
	bounds.top = frame.getPosition().y;
	bounds.width = frame.getSize().x;
	bounds.height = frame.getSize().y;
}

InputField::InputField()
	: isSelected(false), currentString("")
{
	field.setSize(sf::Vector2f(100, 100));
	field.setFillColor(GetNormalColor());
	text.SetString(currentString);
}

void InputField::Update()
{
	ComputeBounds();
	text.SetSize(bounds.width, bounds.height);
	text.SetPosition(field.getPosition());
	text.Update();
}

void InputField::Render(sf::RenderWindow &window)
{
	if (GetIsInteractable())
	{
		if (!isSelected)
			field.setFillColor(GetNormalColor());

		CheckSelection(window);
	}
	else
		field.setFillColor(GetDisabledColor());

	window.draw(field);
	text.Render(window);
}

void InputField::Load(const std::string &texturePath, const std::string &fontPath)
{
	if (texturePath != "")
		if (texture.loadFromFile(texturePath))
			field.setTexture(&texture);

	if (fontPath != "")
		text.Load(fontPath);
}

void InputField::Load(sf::Texture *texture, const sf::Font &font)
{
	if (texture)
		field.setTexture(texture);
	text.Load(font);
}

void InputField::SetFillColor(const sf::Color& color)
{
	field.setFillColor(color);
}

void InputField::SetOutlineColor(const sf::Color &color)
{
	field.setOutlineColor(color);
}

void InputField::SetTextFillColor(const sf::Color& color)
{
	text.SetFillColor(color);
}

void InputField::SetTextOutlineColor(const sf::Color& color)
{
	text.SetOutlineColor(color);
}

void InputField::SetOutlineThickness(float value)
{
	field.setOutlineThickness(value);
}

float InputField::GetOutlineThickness() const
{
	return field.getOutlineThickness();
}

void InputField::SetTextOutlineThickness(float value)
{
	text.SetOutlineThickness(value);
}

float InputField::GetTextOutlineThickness() const
{
	return text.GetOutlineThickness();
}

void InputField::SetSize(const sf::Vector2f &size)
{
	field.setSize(size);
	text.SetSize(size);
}

void InputField::SetSize(float width, float height)
{
	field.setSize(sf::Vector2f(width, height));
	text.SetSize(width, height);
}

const sf::Vector2f& InputField::GetSize() const
{
	return field.getSize();
}

void InputField::SetPosition(const sf::Vector2f &pos)
{
	field.setPosition(pos);
}

void InputField::SetPosition(float x, float y)
{
	field.setPosition(x, y);
}

const sf::Vector2f &InputField::GetPosition() const
{
	return field.getPosition();
}

void InputField::SetTextCharacterSize(unsigned int value)
{
	text.SetCharacterSize(value);
}

unsigned int InputField::GetTextCharacterSize() const
{
	return text.GetCharacterSize();
}

void InputField::SetTextStyle(sf::Text::Style style)
{
	text.SetStyle(style);
}

void InputField::SetCurrentString(const std::string &string)
{
	currentString = string;
	text.SetString(currentString);
}

std::string InputField::GetCurrentString() const
{
	return currentString;
}

void InputField::GetInput(sf::Uint32 unicode)
{
	if (isSelected)
	{
		if (unicode == 8 || unicode == 127)
		{
			if (currentString.size() > 0)
				currentString.erase(currentString.size() - 1);
		}
		else
			currentString += unicode;

		text.SetString(currentString);

		OnValueChanged();

		if (input.GetKey(sf::Keyboard::Enter))
			OnEndEdit();
	}
}

void InputField::Clear()
{
	currentString = "";
	text.SetString("");
}

void InputField::AddOnSelectEvent(const std::shared_ptr<Event>& event)
{
	onSelectEvents += event;
}

void InputField::AddDeselectEvent(const std::shared_ptr<Event> &event)
{
	onDeselectEvents += event;
}

void InputField::AddOnValueChangedEvent(const std::shared_ptr<Event>& event)
{
	onValueChangedEvents += event;
}

void InputField::AddOnEndEditEvent(const std::shared_ptr<Event>& event)
{
	onEndEditEvents += event;
}

void InputField::ComputeBounds()
{
	bounds.left = field.getPosition().x;
	bounds.top = field.getPosition().y;
	bounds.width = field.getSize().x;
	bounds.height = field.getSize().y;
}

void InputField::OnSelect()
{
	onSelectEvents.Invoke();
	isSelected = true;
	field.setFillColor(GetSelectedColor());
}

void InputField::OnDeselect()
{
	onDeselectEvents.Invoke();
	isSelected = false;
	field.setFillColor(GetNormalColor());
}

void InputField::OnValueChanged()
{
	onValueChangedEvents.Invoke();
}

void InputField::OnEndEdit()
{
	onEndEditEvents.Invoke();
	OnDeselect();
}

void InputField::CheckSelection(sf::RenderWindow &window)
{
	ComputeBounds();

	sf::Vector2f mousePosition = sf::Vector2f(
		(float)input.GetMousePosition(window).x,
		(float)input.GetMousePosition(window).y);

	if (bounds.contains(mousePosition))
	{
		if (!isSelected)
		{
			field.setFillColor(GetHighlightedColor());

			if (input.GetMouseButton(sf::Mouse::Left))
				field.setFillColor(GetPressedColor());

			if (input.GetMouseButton(sf::Mouse::Left))
			{
				if (!isSelected)
					OnSelect();
			}
		}
	}
	else
		if (isSelected)
		{
			if (input.GetMouseButton(sf::Mouse::Left))
				OnDeselect();
		}
		else
			field.setFillColor(GetNormalColor());
}

