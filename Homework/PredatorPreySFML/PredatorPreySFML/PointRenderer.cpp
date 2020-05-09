#include "PointRenderer.h"
#include "Context.h"

bme::PointRenderer::PointRenderer(GameObject *owner, Context &context)
	:	Renderer2D(owner, context), point(10)
{

}

void bme::PointRenderer::Render()
{
	Renderer2D::Render();

	GetContext().GetWindow().draw(point, GetWorldTransform());
}

bme::PointRenderer *bme::PointRenderer::Clone(GameObject *owner)
{
	PointRenderer *clone = new PointRenderer(owner, GetContext());
	clone->SetExecutionOrder(GetExecutionOrder());
	clone->point = point;
	clone->SetZOrder(GetZOrder());
	clone->SetIsEnabled(GetIsEnabled());
	clone->SetView(GetView());

	return clone;
}

sf::CircleShape &bme::PointRenderer::GetPoint()
{
	return point;
}
