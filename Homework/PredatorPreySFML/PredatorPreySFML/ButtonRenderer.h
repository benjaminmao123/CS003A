#pragma once

#include <SFML\Graphics.hpp>

#include "Selectable.h"
#include "Renderer2D.h"

namespace bme
{
	class TextRenderer;

	class ButtonRenderer : public Renderer2D, public Selectable
	{
	public:
		ButtonRenderer(GameObject *owner, Context &context);
		
		virtual void Start() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual ButtonRenderer *Clone(GameObject *owner) override;

		void Load(const std::string &path);
		void Load(int id);
		sf::RectangleShape &GetFrame();

	private:
		void ComputeBounds();
		virtual void CheckSelection() override;

		sf::RectangleShape frame;
		sf::FloatRect bounds;
		TextRenderer *text;
	};
}