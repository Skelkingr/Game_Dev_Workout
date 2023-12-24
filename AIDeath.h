#pragma once

#include "AIComponent.h"
#include "AIState.h"

class AIDeath : public AIState
{
public:
	AIDeath() = delete;
	AIDeath(AIComponent* owner) : AIState(owner) {}

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Death"; }
};



