#pragma once

#include "BMEngine.h"

class Movement : public bme::Component
{
public:
	Movement(bme::GameObject *owner, bme::Context &context);

	virtual void Start() override;
	virtual void Update() override;
	virtual Movement *Clone(bme::GameObject *owner) override;

private:
	float speed;
};