#include "UIObjects.h"

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

std::string Text::GetString() const
{
	return text.getString().toAnsiString();
}

void Text::SetColor(const sf::Color &color)
{
	text.setFillColor(color);
}

void Text::SetCharacterSize(float size)
{
	text.setCharacterSize(size);
}

void Text::SetStyle(sf::Text::Style style)
{
	text.setStyle(style);
}

void Text::Load(const std::string &path)
{
	if (font.loadFromFile(path))
		text.setFont(font);
}

void Text::Load(const sf::Font &font)
{
	text.setFont(font);
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

sf::Vector2f Text::GetPosition() const
{
	return sf::Vector2f(rect.left, rect.top);
}

sf::Vector2f Text::GetSize() const
{
	return sf::Vector2f(rect.width, rect.height);
}

void Text::SetString(const std::string &str)
{
	text.setString(str);
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

Selectable::Selectable()
	: normalColor(sf::Color::White), highlightedColor(sf::Color::White),
	pressedColor(sf::Color::White), selectedColor(sf::Color::White),
	disabledColor(sf::Color::White), isInteractable(true),
	isSelected(false)
{

}

Selectable::~Selectable()
{

}

void Selectable::SetNormalColor(const sf::Color &color)
{
	normalColor = color;
}

void Selectable::SetPressedColor(const sf::Color &color)
{
	pressedColor = color;
}

void Selectable::SetHighlightedColor(const sf::Color &color)
{
	highlightedColor = color;
}

void Selectable::SetSelectedColor(const sf::Color &color)
{
	selectedColor = color;
}

void Selectable::SetDisabledColor(const sf::Color &color)
{
	disabledColor = color;
}

void Selectable::SetIsInteractable(bool state)
{
	isInteractable = state;
}

const sf::Color &Selectable::GetNormalColor() const
{
	return normalColor;
}

const sf::Color &Selectable::GetPressedColor() const
{
	return pressedColor;
}

const sf::Color &Selectable::GetHighlightedColor() const
{
	return highlightedColor;
}

const sf::Color &Selectable::GetSelectedColor() const
{
	return selectedColor;
}

const sf::Color &Selectable::GetDisabledColor() const
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

void Selectable::AddEvent(Event *event)
{
	onClickEvents += event;
}

void Selectable::RemoveEvent(Event *event)
{
	onClickEvents -= event;
}

void Selectable::OnClick()
{
	onClickEvents.Invoke();
}

EventHandler &Selectable::GetOnClickEvents()
{
	return onClickEvents;
}

void Selectable::SetIsSelected(bool state)
{
	isSelected = true;
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

std::string Button::GetLabel() const
{
	return text.GetString();
}

const sf::Vector2f &Button::GetSize() const
{
	return frame.getSize();
}

const sf::Vector2f &Button::GetPosition() const
{
	return frame.getPosition();
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

void Button::SetTextColor(const sf::Color &color)
{
	text.SetColor(color);
}

void Button::SetLabelFontSize(float size)
{
	text.SetCharacterSize(size);
}

void Button::SetLabel(const std::string &string)
{
	text.SetString(string);
}

void Button::CheckSelection(sf::RenderWindow &window)
{
	ComputeBounds();

	sf::Vector2f mousePosition = sf::Vector2f(
		float(input.GetMousePosition(window).x),
		float(input.GetMousePosition(window).y));

	if (bounds.contains(mousePosition))
	{
		frame.setFillColor(GetHighlightedColor());

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

void InputField::SetOutlineColor(const sf::Color &color)
{
	field.setOutlineColor(color);
}

void InputField::SetOutlineThickness(const float value)
{
	field.setOutlineThickness(value);
}

void InputField::SetSize(const sf::Vector2f &size)
{
	field.setSize(size);
	text.SetSize(size);
}

void InputField::SetSize(const float width, const float height)
{
	field.setSize(sf::Vector2f(width, height));
	text.SetSize(width, height);
}

void InputField::SetPosition(const sf::Vector2f &pos)
{
	field.setPosition(pos);
}

void InputField::SetPosition(float x, float y)
{
	field.setPosition(x, y);
}

const sf::Vector2f &InputField::GetSize() const
{
	return field.getSize();
}

const sf::Vector2f &InputField::GetPosition() const
{
	return field.getPosition();
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

void InputField::AddOnSelectEvent(Event *event)
{
	onSelectEvents += event;
}

void InputField::AddDeselectEvent(Event *event)
{
	onDeselectEvents += event;
}

void InputField::AddOnValueChangedEvent(Event *event)
{
	onValueChangedEvents += event;
}

void InputField::AddOnEndEditEvent(Event *event)
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
				if (!isSelected)
					OnSelect();
		}
	}
	else
		if (isSelected)
			if (input.GetMouseButton(sf::Mouse::Left))
				OnDeselect();
		else
			field.setFillColor(GetNormalColor());
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

void InputField::SetTextColor(const sf::Color &color)
{
	text.SetColor(color);
}
