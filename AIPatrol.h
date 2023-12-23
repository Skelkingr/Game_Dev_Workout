#pragma once

#include "AIComponent.h"
#include "AIState.h"

class AIPatrol : public AIState
{
public:
	AIPatrol() = delete;
	AIPatrol(AIComponent* owner) : AIState(owner) {}

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Patrol"; }
};

