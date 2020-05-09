#include "Camera2D.h"
#include "Context.h"

bme::Camera2D::Camera2D(GameObject *owner, Context &context)
	:	Component(owner, context)
{
	view.setCenter(GetTransformable().getPosition());
	view.setSize(sf::Vector2f(context.GetWindow().getSize()));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	ComputeViewBounds();
}

void bme::Camera2D::Update()
{
	ComputeViewBounds();
}

bme::Camera2D *bme::Camera2D::Clone(GameObject *owner)
{
	Camera2D *clone = new Camera2D(owner, GetContext());
	clone->view = view;
	clone->viewBounds = viewBounds;
	clone->SetIsEnabled(GetIsEnabled());
	clone->SetExecutionOrder(GetExecutionOrder());

	return clone;
}

void bme::Camera2D::ComputeViewBounds()
{
	viewBounds.left = view.getViewport().left * view.getSize().x;
	viewBounds.top = view.getViewport().top * view.getSize().y;
	viewBounds.width = view.getSize().x;
	viewBounds.height = view.getSize().y;
}
