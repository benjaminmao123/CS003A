#pragma once

#include <string>

#include "Renderer2D.h"

namespace bme
{
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

	class TextRenderer : public Renderer2D
	{
	public:
		TextRenderer(GameObject *owner, Context &context);

		virtual void Update() override;
		virtual void Render() override;
		virtual TextRenderer *Clone(GameObject *owner) override;

		void Load(const std::string &path);
		void Load(int id);
		sf::Text &GetText();
		sf::FloatRect &GetRect();

	private:
		void AlignText();

		sf::Text text;
		sf::Font font;
		HAlign hAlign;
		VAlign vAlign;
		sf::FloatRect rect;
	};
}