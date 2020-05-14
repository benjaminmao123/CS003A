#pragma once

#include "BMEngine.h"

class Movement : public bme::Renderer2D
{
public:
	Movement(bme::GameObject *owner, bme::Context &context);

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual Movement *Clone(bme::GameObject *owner) override;

private:
	float speed;
};