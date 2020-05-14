#pragma once

#ifdef BMENGINE_EXPORTS 
#define DLLEXPORT __declspec(dllexport)  
#else
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <SFML\Graphics.hpp>
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

	class DLLEXPORT Text : public Renderer2D
	{
	public:
		Text(GameObject *owner, Context &context, int zOrder = 0);

		virtual void Update() override;
		virtual Text *Clone(GameObject *owner) override;

		void Load(const std::string &path);
		void Load(int id);
		sf::Text &GetText();
		sf::FloatRect &GetRect();

	protected:
		virtual void Render() override;

	private:
		void AlignText();

		sf::Text text;
		sf::Font font;
		HAlign hAlign;
		VAlign vAlign;
		sf::FloatRect rect;
	};
}