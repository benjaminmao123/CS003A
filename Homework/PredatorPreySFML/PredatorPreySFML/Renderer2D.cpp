#include "Renderer2D.h"
#include "Context.h"

bme::Renderer2D::Renderer2D(GameObject *owner, Context &context, int zOrder)
	:	Component(owner, context), zOrder(zOrder), 
		view(&context.GetWindow().getDefaultView())
{

}

void bme::Renderer2D::Render()
{
	GetContext().GetWindow().setView(*view);
}

int bme::Renderer2D::GetZOrder() const
{
	return zOrder;
}

void bme::Renderer2D::SetZOrder(int value)
{
	zOrder = value;
}

void bme::Renderer2D::SetView(const sf::View *view)
{
	this->view = view;
}

const sf::View *const bme::Renderer2D::GetView() const
{
	return view;
}
